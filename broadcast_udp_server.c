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
int b=1,sock;
struct sockaddr_in serv;
char str1[100],str2[10];
char str3[3]="bye";
bzero(&serv,sizeof(serv));
sock=socket(AF_INET,SOCK_DGRAM,0);
setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&b,sizeof(b));
serv.sin_family=AF_INET;
serv.sin_port=htons(12345);
serv.sin_addr.s_addr=inet_addr("255.255.255.255");
while(1)
{
printf("do you want to send data ");
fgets(str2,10,stdin);
if(strncmp(str2,"yes",3)==0)
{
bzero(str1,100);
printf("enter data: ");
fgets(str1,100,stdin);
sendto(sock,str1,strlen(str1),0,(struct sockaddr *)&serv,sizeof(serv));
}
else{
sendto(sock,str3,strlen(str3),0,(struct sockaddr *)&serv,sizeof(serv));
break;
}
}
close(sock);
}
