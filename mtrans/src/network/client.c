/* --- include statements --- */
#include "client.h"


/* init: initializes a connection with the server */
int init(void){

	int flag;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;


    flag = getaddrinfo(HOST, PORT, &hints, &servinfo);
    if (flag != 0) 
    	return 1;

    for (p = servinfo; p != NULL; p = p -> ai_next) {

    	if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
    	}

    	if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
			continue; 
		}
	
		break;
    }

    if (p == NULL)
    	return 2;

    close(sockfd);

    return 0;

}