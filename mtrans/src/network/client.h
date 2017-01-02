
#ifndef CLIENT_H
#define CLIENT_H


/* --- include statements --- */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>


/* --- define statements --- */
#define PORT "3492"
#define HOST "127.0.0.1"
#define MAXDATASIZE 1000000 // maximum number of bytes than can be transmitted / received

//#typedef struct addrinfo INF;


/* --- function prototypes --- */
int init(void);

/* --- variables --- */
static int sockfd; // the server socket file descriptor
struct addrinfo hints; // "hints" on the detail of the server
struct addrinfo *servinfo;
struct addrinfo *p;

#endif