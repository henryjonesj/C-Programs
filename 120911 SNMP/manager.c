#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>

# define PORTNO 6500

int main(int argc,char *argv[])
{
struct sockaddr_in sa;
char write_buff[50],read_buff[50];
int sockfd,len,i;
sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(sockfd<0)
	{
	printf("sock fail");
	exit(1);
	}
else
	{
	printf("sock created");
	}

bzero(&sa,sizeof(sa));

sa.sin_family=AF_INET;
sa.sin_addr.s_addr=inet_addr("127.0.0.1");
sa.sin_port=htons(PORTNO);

len=sizeof(sa);
bzero(write_buff,sizeof(write_buff));
bzero(read_buff,sizeof(read_buff));

for(i=1;i<argc;i++)
	{	
	//printf("in write_buff--%s\n",write_buff);
	strcat(write_buff,argv[i]);
	strcat(write_buff," ");
	}

printf("write_buff--%s\n",write_buff);
sendto(sockfd,write_buff,sizeof(write_buff),0,(struct sockaddr *)&sa,len);

recvfrom(sockfd,read_buff,sizeof(read_buff),0,(struct sockaddr *)&sa,&len);
printf("recv ids=%s\n",read_buff);
close(sockfd);
}