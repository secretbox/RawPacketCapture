/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 */

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>

#define MY_DEST_MAC0	0xff
#define MY_DEST_MAC1	0xff
#define MY_DEST_MAC2	0xff
#define MY_DEST_MAC3	0xff
#define MY_DEST_MAC4	0xff
#define MY_DEST_MAC5	0xff

#define DEFAULT_IF	"eth0"
#define BUF_SIZ		1024
#define REC_BUF_SIZE	1500
void main(int argc, char *argv[])
{
	printf("Start to Define Variable");
	struct ifreq ifpro;
	int sockfd;
	char recbuff[REC_BUF_SIZE];
	char ifName[5];
	int tx_len = 0;
	int stat=0;
	
	if (argc > 1){
		strcpy(ifName, argv[1]);
	} else {
		strcpy(ifName, DEFAULT_IF);
	}
	printf("Open RAW socket");
		  
	if ((sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) == -1) {
	    perror("socket");
	}
	printf("Get INterface");
	/* Set interface to promiscuous mode - do we need to do this every time? */
	strncpy(ifopts.ifr_name, ifName, IFNAMSIZ-1);
	ioctl(sockfd, SIOCGIFFLAGS, &ifopts);
	ifopts.ifr_flags |= IFF_PROMISC;
	ioctl(sockfd, SIOCSIFFLAGS, &ifopts);
	/* Allow the socket to be reused - incase connection is closed prematurely */
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof sockopt) == -1) {
		perror("setsockopt");
		close(sockfd);
		exit(EXIT_FAILURE);
	}	



	printf("Start to capture packet");
	stat = recv(sockfd,recbuff,sizeof(recbuff),0); 
	if ( stat != 0) printf("error on recv");
	printf("Receive packet : %x",stat);

	


}
