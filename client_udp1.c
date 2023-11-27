#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
int main()
{
int r=1;
int sock;
struct sockaddr_in serv;
char str1[100],str2[10];
bzero(&serv,sizeof(serv));
sock=socket(AF_INET,SOCK_DGRAM,0);
setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&r,sizeof(r));
serv.sin_family=AF_INET;
serv.sin_port=htons(12345);
serv.sin_addr.s_addr=INADDR_ANY;
bind(sock,(struct sockaddr *)&serv,sizeof(serv));
while(1)
{
bzero(str2,10);
if(strncmp(str2,"bye",3)==0){break;}else{
bzero(str1,100);
recvfrom(sock,str1,100,0,NULL,NULL);
printf("recvd data is %s",str1);}
}
close(sock);
}
