#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>

//SERVER

# define PORTNO 6500  // same as the other one
struct data
	{
	char *data1;
	char *data2;
	};

struct node
	{
	struct node *lnode;
	struct node *rnode;
	char *id;
	struct data *d;
	}*root;

void insert(char *str,char *n1,char *n2) // bin tree insertion
	{
	struct node *temp;
	struct node *prev,*nnew;
	
	temp=root;

	nnew=(struct node *)malloc(sizeof(struct node));
	nnew->id=str;
	nnew->lnode=NULL; nnew->rnode=NULL;

	nnew->d=(struct data*)malloc(sizeof(struct data));
	(nnew->d)->data1=(char *)malloc(100*sizeof(char));
	(nnew->d)->data2=(char *)malloc(100*sizeof(char));

	strcpy((nnew->d)->data1,n1);
	strcpy((nnew->d)->data2,n2);

	while(temp!=NULL)
		{
		prev=temp;
		if(strcmp((temp->id),str)>0)
			{
			temp=temp->lnode;
			}
		else
			{
			temp=temp->rnode;
			}
		}

	if(strcmp(str,(prev->id))<0)
		prev->lnode=nnew;
	else
		prev->rnode=nnew;
	}


char* retrieve(char *idstr)
	{
	int y;
	char *s, *t;
	char tem;

	t=(char *)malloc(100*sizeof(char));

	struct node *temp=root;
	while(temp!=NULL)
		{
		if(strcmp(temp->id,idstr)==0)
			{
			s=(temp->d)->data1;
			strcat(t,s);
			strcat(t,",");

			s=(temp->d)->data2;
			strcat(t,s);strcat(t," ");
			printf("in if--%s",t);
			break;
			}
		
		else if(strcmp(temp->id,idstr)>0)
			{
			temp=temp->lnode;
			}
		else
			{		
			temp=temp->rnode;
			}
		}

	if(strlen(t)==0)
		{
		strcpy(t,"not found");
		}
	printf("n--%s",t);
	return t;
	}



void mytree()
	{
	root->id="5";
	root->lnode=NULL;
	root->rnode=NULL; 

	root->d=(struct data*)malloc(sizeof(struct data));
	(root->d)->data1="10";
	(root->d)->data2="15";

	insert("1","2","30");
	insert("6","45","6");
	insert("3","8","90");
	insert("2","9","10");
	}


char* func(char *cont)
	{
	char *str="";
	str=(char*)malloc(300*sizeof(char));

	int i,k=0;
	char temp[100]="";

	for(i=0;i<strlen(cont);i++)
		{
		if(cont[i]==' ')
			{	
			temp[k]='\0';
			strcat(str," ");
			strcat(str,temp);
			strcat(str,":");
			strcat(str,retrieve(temp));
			printf("ppppi%s",str);
			strcpy(temp,"");
			k=0;
			}
		else
			{
			temp[k++]=cont[i];
			}
		}
	temp[k]='\0';
	
	printf("pppp%s",str);
	return str;
	}


int main(int argc,char *argv[])
{
int sockfd,len;
char read_buff[100],buff[100];
struct sockaddr_in cl,sa;
int i,c,fl=0;

root=(struct node *)malloc(sizeof(struct node));
mytree();

sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(sockfd<0)
	{
	printf("sock fail");
	exit(0);
	}
else
	{
	printf("sock created\n");
	}

sa.sin_family=AF_INET;
sa.sin_addr.s_addr=htonl(INADDR_ANY);
sa.sin_port=htons(PORTNO);

if(bind(sockfd,(struct sockaddr *)&sa,sizeof(sa))<0)
	{
	printf("bind fail");
	exit(0);
	}
else
	{
	printf("binded\n");
	}

bzero(read_buff,sizeof(read_buff));
len=sizeof(cl);

recvfrom(sockfd,read_buff,sizeof(read_buff),0,(struct sockaddr *)&cl,&len);
printf("\nrecvd: %s",read_buff);

bzero(write_buff,sizeof(write_buff));
strcpy(write_buff,func(read_buff));

sendto(sockfd,write_buff,sizeof(write_buff),0,(struct sockaddr *)&cl,len);
close(sockfd);
}