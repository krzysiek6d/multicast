/* Send Multicast Datagram code example. */
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[ ])
{
	int sd = socket(AF_INET, SOCK_DGRAM, 0); 
	if(sd < 0)	
	{
		perror("Opening datagram socket error"); 
		exit(1);
	}
	 
	sockaddr_in groupSock = {};
	groupSock.sin_family = AF_INET;
	groupSock.sin_addr.s_addr = inet_addr("226.1.1.1");
	groupSock.sin_port = htons(4321);
	 
	struct in_addr localInterface;
	localInterface.s_addr = inet_addr("192.168.1.4");
	if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0)
	{
		perror("Setting local interface error");
		exit(1);
	}
	else
		printf("Setting the local interface...OK\n");
	
	char databuf[1024] = "Multicast test message!";
	int datalen = sizeof(databuf);
	while(true)
	{
 		if(sendto(sd, databuf, datalen, 0, (struct sockaddr*)&groupSock, sizeof(groupSock)) < 0)
			perror("Sending datagram message error");
		else
			printf("Sending datagram message...OK\n");
		sleep(1);
	}
	return 0;
}
