#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
#include<arpa/inet.h>
int main(int argc,char **argv)
{
 int sock_fd,n;
 char sendline[100];
 char recvline[100];
 struct sockaddr_in servaddr;
 sock_fd=socket(AF_INET,2,0);
 bzero(&servaddr,sizeof servaddr);
 servaddr.sin_family=AF_INET;
 servaddr.sin_port=htons(22000);
 servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
 //inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
 int my_input;
 
 while(1)
 {
 int len = sizeof(servaddr);
 bzero( sendline, 100);
 bzero( recvline, 100);
 fgets(sendline,100,stdin); /*stdin = 0 , for standard input */
 if(strncmp("exit",sendline,4)==0)  {
 printf("Client Exited \n");
//  close(sock_fd);
 break;
 }
 sendto(sock_fd,sendline,strlen(sendline),0,(struct sockaddr *) &servaddr,len);
 recvfrom(sock_fd,recvline,sizeof(recvline),0,(struct sockaddr *) &servaddr,&len);
 if(strncmp("exit",recvline,4)==0)  {
 printf("Server Closed \n");
//  close(sock_fd);
 break;
 }
 printf("Recieved from server  - %s",recvline);
 }
}

/*
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
#include<unistd.h>

int main()
{
 char str[100];
 char sendline[100];
 int listen_fd;
 struct sockaddr_in servaddr,claddr;
 listen_fd = socket(AF_INET, 2, 0);
 bzero( &servaddr, sizeof(servaddr));
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 servaddr.sin_port = htons(22000);
 bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 listen(listen_fd, 10);

 while(1)
 {
 int len = sizeof(claddr);
 bzero( sendline, 100);
 bzero( str, 100);
 recvfrom(listen_fd,str,sizeof(str),0,(struct sockaddr *) &claddr,&len);
 printf("Recieved from client  - %s",str);
 fgets(sendline,100,stdin);
 sendto(listen_fd,sendline,strlen(sendline),0,(struct sockaddr *) &claddr,len);
 if(strncmp("exit",sendline,4)==0)  {
 printf("Server Closed \n");
 close(listen_fd);
 break;
 }
 }
}
*/