#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include<ctype.h>
int main()
{
int sock;
int addr_len, bytes_read;
char recv_data[1024],send_data[1024];
struct sockaddr_in server_addr , client_addr;
if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
perror("Socket Error");
exit(1);
}
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(8000);
server_addr.sin_addr.s_addr = INADDR_ANY;
bzero(&(server_addr.sin_zero),8);
if (bind(sock,(struct sockaddr *)&server_addr,
sizeof(struct sockaddr)) == -1){
perror("Bind Error");
exit(1);
}
addr_len = sizeof(struct sockaddr);
printf("\n UDP Server Waiting for client on port 8000\n\n");
fflush(stdout);
while (1){
bytes_read = recvfrom(sock,recv_data,1024,0,
(struct sockaddr *)&client_addr, &addr_len);
recv_data[bytes_read] = '\0';
if((strcmp(recv_data,"q")==0)||strcmp(recv_data,"Q")==0)
break;
else{
printf("\nClient : %s",recv_data);
fflush(stdout);
//Process Request to convert it to lowercase()
for(int i=0;i<bytes_read;i+=1)
if(recv_data[i] >= 65 && recv_data[i] <= 90)
send_data[i]=recv_data[i]+32;
else send_data[i]=recv_data[i];
send_data[bytes_read]='\0';
printf("\nServer : %s",send_data);
sendto(sock,send_data,strlen(send_data),0,(struct
sockaddr*)&client_addr,sizeof(struct sockaddr));
}}
return 0;}


