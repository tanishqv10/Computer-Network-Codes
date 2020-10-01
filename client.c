#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>

void main(){

	struct sockaddr_in server,client;
	int sock,clientSocket,bytes;
	char receivedBytes[1024],sendBytes[1024];
	if((sock = socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("Invalid Socket Descriptor");
		exit(1);	
	}
	
	server.sin_family = AF_INET;
	server.sin_port = htons(5005);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server.sin_zero),8);

	if(connect(sock,(struct sockaddr *)&server,sizeof(server)) == -1){
		perror("Unable to connect");
		exit(1);
	} 
	
	while(1){
		
		printf("\nEnter 1st number: ");
		gets(sendBytes);
		bytes=send(sock,sendBytes,1024,0);
		printf("\nEnter 2st number: ");
		gets(sendBytes);
		bytes=send(sock,sendBytes,1024,0);
		printf("\nEnter the operand or quit: ");
		gets(sendBytes);
		bytes=send(sock,sendBytes,1024,0);
		if(strcmp(sendBytes,"e")==0 || strcmp(sendBytes,"E")==0){
		printf("\nClient exiting...");
		close(sock);
		exit(1);
		}
		bytes=recv(sock,receivedBytes,1024,0);
		receivedBytes[bytes]='\0';
		printf("\nServer: %s",receivedBytes);
		if(strcmp(receivedBytes,"e")==0 || strcmp(receivedBytes,"E")==0){
		printf("\nServer going off...");
		close(sock);
		break;
		}
		
		
		/*printf("\nClient: ");
		gets(sendBytes);
		bytes = send(sock,sendBytes,1024,0);
		if(strcmp(sendBytes,"q") == 0 || strcmp(sendBytes,"Q") == 0){
			printf("\nClient exiting...");
			close(sock);
			exit(1);
		}
		bytes = recv(sock,receivedBytes,1024,0);
		receivedBytes[bytes] = '\0';
		printf("\nServer: %s",receivedBytes);
		if(strcmp(receivedBytes,"q") == 0 || strcmp(receivedBytes,"Q") == 0){
			printf("\nServer going off...");
			close(sock);
			break;
		}*/
	}
}
/*
socket()
connect()
recv()
send()
*/
