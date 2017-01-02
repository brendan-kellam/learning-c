 
/*
** server.c -- a stream socket server demo
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT "3491" // usage port
#define BACKLOG 10 // how many pending connections that can queue


void sigchld_handler(int s){

	// waitpid() might overwrite errno, so we save and restore
	int saved_errno = errno;

	while(waitpid(-1, NULL, WNOHANG) > 0);

	errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa){

	if (sa->sa_family == AF_INET) { // IPv4
		return &(((struct sockaddr_in *) sa) -> sin_addr); // return the IP address
	}

	return &(((struct sockaddr_in6 * ) sa) -> sin6_addr);
}

int main(void){
	int sockfd, new_fd; // listen on sock_fd, new connection on new_fd
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	int yes = 1;
	char s[INET6_ADDRSTRLEN], msg[] = "Hello, world! This is a dynamic test";
	int rv;

	// initialize the memory of the hints structure
	memset(&hints, 0, sizeof hints);

	// fill out hints
	hints.ai_family = AF_UNSPEC; // either IPV4 or IPV6	
	hints.ai_socktype = SOCK_STREAM; // stream communication
	hints.ai_flags = AI_PASSIVE; // use my IP

	// initialize and get information about the future connection 
	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) { // if this command fails
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}

	// loop through all the results found in the linked list and bind to the first available
	for (p = servinfo; p != NULL; p = p->ai_next) {
			
		// attempt to initialize the socket file descriptor
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) { // if error occurs
			perror("server: socket");
			continue;
		}

		// set the newly initialized socket's options
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) { // if error occurs
			perror("setsockopt");
			exit(2);
		}

		// attempt to bind the socket to the given port
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) { // if error occurs
			close(sockfd);
			perror("server: bind");
			continue;
		}

		// connection initialized
		break;
	}
		
	freeaddrinfo(servinfo); // all done with this structure


	if (p == NULL) { // on failure to bind
		fprintf(stderr, "server: failed to bind\n");
		exit(3);
	}

	if (listen(sockfd, BACKLOG) == -1) { // attempt to listen on the connected socket
		perror("listen");
		exit(4);
	}

	sa.sa_handler = sigchld_handler; // reap all dead processes 
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(5);
	}

	printf("server: waiting for connections...");

	while(1) { // main accept() loop
		sin_size = sizeof their_addr;
		
		// attempt to accept a new connection
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) { // on error
			perror("accept");
			continue;
		}


		// converts the network address structure (IP) into a character string
		inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
		printf("server: got connection from %s\n", s);

		if (!fork()) { // this is the child process
			close(sockfd); // child doesn't need the listener

			// attempt to send a message to client
			if (send(new_fd, msg, sizeof(msg), 0) == -1) // if error occurs
				perror("send");
			close(new_fd);
			exit(0);
		}
		close(new_fd); // parent doesn't need this
	}

	return 0;
}
