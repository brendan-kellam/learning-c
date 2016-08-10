
/*
Some notes:
    There are many different types of sockets, this program will only deal with Internet sockets
    Internet sockets, 2 types:
        1. Stream Sockets
            - Forms a direct connection between two clients
            - Utilizes TCP
        2. Datagram Sockets
            - A connectionless system that does not ensure sequential and complete data
            - Utilizes UDP
            - Optimal for online gaming, video confencing etc. (where lossed packets do not matter)
 
 
    Transmission Control Protocol (TCP) ensures data arrives sequentially and error-free
    User Datagram Protocol (UDP)
 
    A layered model (for unix systems):
                --- TOP ---
    Application Layer (telnet, ftp, etc.)
    Host-to-Host Transport Layer (TCP, UDP)
    Internet Layer (IP and routing)
    Network Access Layer (Ethernet, wi-fi, etc.)
                --- BOTTOM ---
    
    Both TCP and UDP use a 16-bit socket number. This number is like a local adress for a given network
    
    Network Byte Order: Big-Endian
    Host Byte Order (I.E Intel machines (so mine)): Little-Endian
    Due to the differences, a converstion to Network Byte Order must always be preformed
        htons() - host to network short
        htonl() - host to network long
        ntohs() - network to host short
        ntohl() - network to host long

    ---------- Structures to be used: ----------
	
	--- addrinfo ---
    struct addrinfo {
	    int              ai_flags;     // AI_PASSIVE, AI_CANONNAME, etc.
	    int              ai_family;    // AF_INET, AF_INET6, AF_UNSPEC
	    int              ai_socktype;  // SOCK_STREAM, SOCK_DGRAM
	    int              ai_protocol;  // use 0 for "any"
	    size_t           ai_addrlen;   // size of ai_addr in bytes
	    struct sockaddr *ai_addr;      // struct sockaddr_in or _in6
	    char            *ai_canonname; // full canonical hostname
	    struct addrinfo *ai_next;      // linked list, next node
	};

	--- sockaddr ---
	struct sockaddr {
	    unsigned short    sa_family;    // address family, AF_xxx, AF_INET (IPv4), AF_INET6 (IPv6)
	    char              sa_data[14];  // 14 bytes of protocol address
	};
	
	---
		theory: sockaddr was deemed to be annoying to deal with, so programmers created
		sockaddr_in ("in" for "internet"). struct sockaddr_in can be casted to a pointer
		type struct sockaddr, and vice-versa!
	---

	--- sockaddr_in (IPv4 ONLY!) ---
	struct sockaddr_in {
	    short int          sin_family;  // address family, AF_xxx, AF_INET (IPv4), AF_INET6 (IPv6)
	    unsigned short int sin_port;    // Port number (must be in Network Byte Order!!!)
	    struct in_addr     sin_addr;    // Internet address (IP address)
	    unsigned char      sin_zero[8]; // Same size as struct sockaddr (set to all zero using memset)
	};

	
	--- in_addr (Internet address)(IPv4 ONLY!) --- 
	// Internet address (a structure for historical reasons)
	struct in_addr {
	    uint32_t s_addr; // that's a 32-bit int (4 bytes)
	    // ^^refers to the 4-byte IP address (in Network Byte Order)
	};
	

	--- sockaddr_in6 (IPv6 ONLY!) ---
	struct sockaddr_in6 {
		u_int16_t 		sin6_family;   // address family, AF_INET6
		u_int16_t 		sin6_port;     // port number, Network Byte Order
		u_int32_t		sin6_flowinfo; // IPv6 flow information
		struct in6_addr sin6_addr;     // IPv6 address
		u_int32_t       sin6_scope_id; // Scope ID
	};

	--- in6_addr (Internet address)(IPv6 ONLY!) ---
	struct in6_addr {
	    unsigned char   s6_addr[16];   // IPv6 address
	};


	--- sockaddr_storage ---
	struct sockaddr_storage {
	    sa_family_t  ss_family;     // address family
	    // all this is padding, implementation specific, ignore it:
	    char      __ss_pad1[_SS_PAD1SIZE];
	    int64_t   __ss_align;
	    char      __ss_pad2[_SS_PAD2SIZE];
	};


	---------- Info on usage ----------

	--- 1. To convert a IP address (ex: 10.12.110.57) into a  struct in_addr --- 
	struct sockaddr_in sa; // IPv4
	struct sockaddr_in6 sa6; // IPv6
	
	inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr)); // IPv4
	inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr)); // IPv6
	
	important function: inet_pton - ("IP _ presentation to network notation")
		- This function returns -1 on error, or 0 if the address is messed up
		  SO ENSURE ERROR CHECKING!!

	
	--- 2. To convert a struct in_addr into IP address notation ---
	// IPv4:
	char ip4[INET_ADDRSTRLEN];  // space to hold the IPv4 string
	struct sockaddr_in sa;      // pretend this is loaded with something
	
	inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);
	printf("The IPv4 address is: %s\n", ip4);
	

	// IPv6:
	char ip6[INET6_ADDRSTRLEN]; // space to hold the IPv6 string
	struct sockaddr_in6 sa6;    // pretend this is loaded with something
	
	inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);
	
	printf("The address is: %s\n", ip6);

	important function: inet_ntop() - ("IP network notation to presentation")
	important macros: INET_ADDRSTRLEN/INET6_ADDRSTRLEN - largest size string a IP address can be
	

	---------- Socket system calls ----------
	#include <sys/types.h> // required imports
	#include <sys/socket.h>

	int socket(int domain, int type, int protocol); // important function
	
	purpose: 
		Creates a new socket for your program

	parameters:
		domain: IPV4 or IPv6 [PF_INET or PF_INET6]
		type: stream or datagram [SOCK_STREAM or SOCK_DGRAM]
		protocol: TCP or UDP [set to 0 to choose proper protocol given type] {getprotobyname() can also 
			be used with a look up of either "tcp" or "udp"}

	returns:
		int - socket descriptor used for later system calls, or -1 on error.
	
	---------- Bind system calls ----------
	#include <sys/types.h>
	#include <sys/socket.h>
	
	int bind(int sockfd, struct sockaddr *my_addr, int addrlen);

	purpose:
		to "bind" the newly created socket to pre-existing port as specified by getaddrinfo()
		-- NOTE: bind will mainly be used by SERVER applications

	parameters:
		sockfd: the socket file descriptor as returned by socket();
		*my_addr: pointer to a struct sockaddr as provided by getaddrinfo()
		addrlen: length in bytes of the address


	---------- Connect system calls ----------
	#include <sys/types.h>
	#include <sys/socket.h>

	int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
	
	purpose:
		allows for the connection to a remote host

	parameters:
		sockfd: the socket file descriptor
		*serv_addr: pointer to a struct sockaddr containing the destination port and IP address
		addrlen: length in bytes of the server adress structure

	returns:
		int: -1 on error


	---------- Listen system calls ----------
	#include <sys/types.h>
	#include <sys/socket.h>

	int listen(int sockfd, int backlog);

	purpose:
		listen waits for incoming connections (essentially listing) ready to handle them in some way

	parameters:
		sockfd: the socket file descriptor
		backlog: a integer representing the number of concurrent connections that can be handled in the
			queue at one time. A connection is removed from the queue by calling connect();

	returns:
		int: -1 on error

	notes: a sample process for listing to incoming connections
		getaddrinfo();
		socket();
		bind();
		listen();
		// accept() goes here


	---------- Accept system calls ----------
	#include <sys/types.h>
	#include <sys/socket.h>
	
	int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

	purpose: 
		To accept and establish a new connection with another computer. When calling connect(),
		the system will create a NEW socket for this newly created conversation. As such, connect()
		returns a brand new socket file descriptor (int sockfd)
	
	parameters:
		sockfd: the listen()ing socket descriptor (I.E the original socket descriptor created)
		*addr: pointer to a struct sockaddr or struct sockaddr_storage that will hold information about
			the incoming connection.
		*addrlen: a local integer varible that should be set to: sizeof(struct sockaddr_storage). connect()
			will NOT put anymore bytes into *addr. If it puts less, *addrlen will reflect that fluctuation.

	returns:
		int: a new socket file descriptor for the connect / -1 on error

	
	---------- Send and Receive system calls ----------
	#include <sys/types.h>
	#include <sys/socket.h>

	int send(int sockfd, const void *msg, int len, int flags);
	int recv(int sockfd, void *buf, int len, int flags);


	purpose:
		These two functions allow for communication over STREAM sockets or connected DATAGRAM sockets.
		Regular unconnected datagram sockets must utilize sendto() and recvfrom() functions outlined bellow.

	parameters [send()]:
		sockfd: socket file descriptor for the socket you want data to be sent to
		msg: pointer to the data that needs to be sent
		len: length in bytes of said data
		flags: set to 0 for default behavior

	returns [send()]:
		int: the number of bytes ACTUALLY sent out. This number might be less than the length of the total data sent,
			and as such MUST be compared. -1 on error



	parameters [recv()]:
		sockfd: socket file descriptor to read from
		buf: a buffer to read the incoming data into
		len: the maximum length of the buffer
		flags: set to 0 for default behavior


	returns [recv()]:
		int: number of bytes actually read into the buffer, or, -1 on error.
			NOTE - if recv() returns 0, this means the remote side closed the connection on you!
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "net.h"

// yields a pointer to a linked list (res)
int getaddrinfo(const char *node, // e.g. "www.example.com" or IP
				const char *service, // e.g. "http" or port number
				const struct addrinfo *hints, // points to a struct addrinfo w/ relevant info
				struct addrinfo **res);

// test function that sets-up a client
void tutclnt(){
	int status;
	struct addrinfo hints;
	struct addrinfo *servinfo;  // will point to the results

	memset(&hints, 0, sizeof hints); // make sure the struct is empty
	hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

	// get ready to connect
	status = getaddrinfo("www.example.net", "3490", &hints, &servinfo);
	
	// servinfo now points to a linked list of 1 or more struct addrinfos
	// etc.
}


// test function that sets-up a server to listen to connections
void tutsvrlisten(){
	int status;
	struct addrinfo hints;
	struct addrinfo *servinfo; // will point to the results

	memset(&hints, 0, sizeof hints); // makesure struct is empty

	hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
	hints.ai_flags = AI_PASSIVE; // fill in my IP for me

	if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    	exit(1);
	}

	// servinfo now points to a linked list of 1 or more struct addrinfos
	
	// ... do everything until you don't need servinfo anymore ....
	
	freeaddrinfo(servinfo); // free the linked-list
}


// basic implementation of sockets
void tutsocket(){
	int socketfd;
	struct addrinfo hints, *res;

	memset(&hints, 0, sizeof hints); // ensure hints is memory initialized

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((status = getaddrinfo(NULL, "3490", &hints, &res)) != 0){
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    	exit(1);
	}

	socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	// bind the socket to the port passed into getaddrinfo
	bind(sockfd, res->ai_addr, res->ai_addrlen);

	/* to remove the "Address already in use" error message: */
	int yes = 1;

	if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1){
		perror("setsockopt");
		exit(1);
	}

}

// basic implementation of connect
void tutconnect(){	
	struct addrinfo hints, *res;
	int socketfd;

	memset(&hints, 0, sizeof hints);

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo("www.example.com", "3490", &hints, &res);

	// create a new socket
	socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	//connect!
	connect(sockfd, res->ai_addr, res->ai_addrlen);
}

// basic implementation of accept
#define MYPORT "3490"
#define BACKLOG 10

void tutaccept(){
	struct sockaddr_storage their_addr; // the connection's details
	socklen_t addr_size;
	struct addrinfo hints, *res;
	int sockfd, new_fd; // new_fd: the newly created socket file descriptor

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    getaddrinfo(NULL, MYPORT, &hints, &res);

    // make a socket, bind it and listen
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    bind(sockfd, res->ai_addr, res->ai_addrlen);
    listen(sockfd, BACKLOG);

    // accept incoming connections:

    addr_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

    // ready to communicate on new_fd!

}

int main(){
	print(BLU "running.." RESET);
	return 0;
}