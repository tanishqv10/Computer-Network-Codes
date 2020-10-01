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
	int sock,clientSocket,n1,n2,flag=0,bytes,result;
	char operand,receivedBytes[1024],sendBytes[1024];
	if((sock = socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("Invalid Socket Descriptor");
		exit(1);	
	}
	
	server.sin_family = AF_INET;
	server.sin_port = htons(5005);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server.sin_zero),8);

	if(bind(sock,(struct sockaddr *)&server,sizeof(server)) == -1){
		perror("Unable to bind");
		exit(1);
	}
	
	if(listen(sock,5) == -1){
		perror("Unable to listen");
		exit(1);
	}
	printf("Server waiting for client...");
	fflush(stdout); 

	while(1){
		int len = sizeof(client);
		clientSocket = accept(sock,(struct sockaddr *)&client,&len);
		if(clientSocket == -1){
			perror("Connection error");
			exit(1);
		}
		printf("I recevied a connection from %s on port %d",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
	
		while(1){
			printf("\n REceiving first number");
			bytes = recv(clientSocket,receivedBytes,1024,0);
			receivedBytes[bytes] = '\0';
			n1=atoi(receivedBytes);
			printf("\n REceiving second number");
			bytes = recv(clientSocket,receivedBytes,1024,0);
			receivedBytes[bytes] = '\0';
			n2=atoi(receivedBytes);
			printf("\n REceiving operand number");
			bytes = recv(clientSocket,receivedBytes,1024,0);
			receivedBytes[bytes] = '\0';
			operand=receivedBytes[0];
			switch(operand){
			        case '+':
			        result=n1+n2;
			        sprintf(sendBytes, "%d", result);
			        break;
			        case '-':
			        result=n1-n2;
			        sprintf(sendBytes, "%d",result);
			        case '*':
			        result=n1*n2;
			        sprintf(sendBytes, "%d", result);
			        break;
			        case '/':
			        result=n1/n2;
			        sprintf(sendBytes, "%d",result);
			        case '%':
			        result=n1%n2;
			        sprintf(sendBytes, "%d", result);
			        break;
			        case 'e':
			        printf("Client wants to exit....");
			        flag=1;
			       
			}
			
			if(flag==1){
			        close(clientSocket);
			        break;
			}
			
			printf("\nSending result...");
			bytes = send(clientSocket,sendBytes,1024,0);
			printf("\nServer: ");
			
			/*if(strcmp(receivedBytes,"q") == 0 || strcmp(receivedBytes,"Q") == 0){
				printf("\nClient want to exit...");
				printf("\nWaiting for new client...");
				close(clientSocket);
				break;
			}
			printf("\nServer: ");
			gets(sendBytes);
			bytes = send(clientSocket,sendBytes,1024,0);
			if(strcmp(sendBytes,"q") == 0 || strcmp(sendBytes,"Q") == 0){
				printf("\nServer going off...");
				close(clientSocket);
				exit(1);
			}*/			
		}
	}
}

/*
socket()
bind()
listen()
accept()
recv()
send()
*/
