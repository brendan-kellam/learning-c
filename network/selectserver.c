/*
** selectserver.c -- a cheezy multiperson chat server
** usage: telnet hostname port

specification of select(): - synchronous I/O multiplexing

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int select(int numfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

description:
	select() gives you the power to monitor several sockets at the same time. It'll tell you which ones are ready for reading, 
	which are ready for writing, and which sockets have raised exceptions, if you really want to know that.

useful macros:

	FD_SET(int fd, fd_set *set);	Add fd to the set.
	FD_CLR(int fd, fd_set *set);	Remove fd from the set.
	FD_ISSET(int fd, fd_set *set);	Return true if fd is in the set.
	FD_ZERO(fd_set *set);			Clear all entries from the set.
	  

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


#define PORT "9034"   // port we're listening on

// get IP address from sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa){
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
	}

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// sendall: ensures ALL data is sent, or error is returned
int sendall(int s, char *buf, int *len){
    
    int total = 0;        // how many bytes we've sent
    int bytesleft = *len; // how many we have left to send

    int n;
    while(total < *len) {
        n = send(s, buf+total, bytesleft, 0);
        if (n == -1) break;
        total += n;
        bytesleft -= n;
	}

    *len = total; // return number actually sent here
    return n==-1?-1:0; // return -1 on failure, 0 on success
}

int main(void){
	fd_set master;    // master file descriptor list
    fd_set read_fds;  // temp file descriptor list for select()
	int fdmax; 		  // maximum file descriptor number

	int listener;	  // listening socket descriptor
	int newfd;		  // newly accept()ed socket descriptor
	struct sockaddr_storage remoteaddr; // client address
	socklen_t addrlen;

	char buf[256]; // buffer for client data
	int nbytes;

	char remoteIP[INET6_ADDRSTRLEN];

	int yes = 1; // for setsockopt() SO_REUSEADDR, below
	int i, j, rv;

	struct addrinfo hints, *ai, *p;

	FD_ZERO(&master); // clear the master and temp sets
	FD_ZERO(&read_fds);

	// get us a socket and bind it
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
	    fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
	    exit(1);
	}

	for(p = ai; p != NULL; p = p->ai_next) {
    	listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    	if (listener < 0) {
			continue; 
		}

	    // lose the pesky "address already in use" error message
	    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	    if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
	    	close(listener);
			continue; 
		}
		break; 
	}

	// if we got here, it means we didn't get bound
	if (p == NULL) {
	    fprintf(stderr, "selectserver: failed to bind\n");
		exit(2); 
	}

	freeaddrinfo(ai); // all done with this

	// listen
	if (listen(listener, 10) == -1) {
	    perror("listen");
		exit(3); 
	}

	// add the listener to the master set
	FD_SET(listener, &master);

	// keep track of the biggest file descriptor
	fdmax = listener; // so far, it's this one

	// main loop
	for(;;) {
	    read_fds = master; // copy it

	    if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) { // create a select() multiplexing I/O to handle multiple sockets
	        perror("select");
			exit(4); 
		}

	    // run through the existing connections looking for data to read
	    for(i = 0; i <= fdmax; i++) {
	    	if (FD_ISSET(i, &read_fds)) { // we got one!!
	    		
	    		if (i == listener) { // if the given file descriptor corresponds
	    							 // to the listener socket, continue
	    			// handle new connections
	    			addrlen = sizeof remoteaddr;

	    			// accept the new connection, creating a new connection socket
	    			newfd = accept(listener, (struct sockaddr *) &remoteaddr, &addrlen);

	    			if (newfd == -1) { 
	    				perror("accept");
	    			} else {
	    				FD_SET(newfd, &master); // add new socket file descriptor to master set
	    				if (newfd > fdmax) {
	    					fdmax = newfd;
	    				}
	    				const char *addrstr = inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr*)&remoteaddr), remoteIP, INET6_ADDRSTRLEN);
	    				printf("selectserver: new connection from %s on socket %d\n", addrstr, newfd);
	    			}

	    		} else { // socket is client
	    			// handle data from client

	    			if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0) {
	    				// got error or connection closed by client
	    				if (nbytes == 0) { // connection closed
	    					printf("selectserver: socket %d hung up\n", i);
	    				} else { // if a error has occured 
	    					perror ("recv");
	    				}
	    				close(i); // bye! - close the client's socket
	    				FD_CLR(i, &master); // remove client socket's file descriptor from master set
	    			
	    			} else { // data was transmitted from client
	    				printf("socket %d: %.*s", i, nbytes, buf);

	    				// loop through all possible file descriptors
	    				for (j = 0; j <= fdmax; j++) {
	    					// send to everyone!
	    					if (FD_ISSET(j, &master)) {
	    						// do not send to the listener and the owner client
	    						if (j != listener && j != i) {
	    							// relay the data

	    							int bytes_sent;
	    							if (bytes_sent = sendall(j, buf, nbytes) == -1) {
	    								perror("send");
	    								printf("%d bytes / %d bytes sent...", bytes_sent, nbytes);
	    							}

	    							
	    						}
	    					}
	    				}

	    			}

	    		} // END handle data from client
	    	} // END got new incoming connection
	    } // END looping through file descriptors
	} // END for(;;)--and you thought it would never end!

	return 0;
}


