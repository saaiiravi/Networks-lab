#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main()
{
	int s,t,len,a;
	FILE *fp;
	struct sockaddr_in rem;
	char str[100],current_ip[100];
	char quit;
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		perror("socket");
		exit(1);
	}
	printf("Connecting...%s\n","127.0.0.1");
	bzero((char *)&rem,sizeof(rem));
	rem.sin_family=AF_INET;
	rem.sin_port=htons(5559);
	rem.sin_addr.s_addr=inet_addr("127.0.0.1");
	a=connect(s,(struct sockaddr *)&rem,sizeof(rem));
	if(a==-1)
	{
		perror("connect");
		exit(1);
	}
	
	printf("connected\n");
	if((t=recv(s,str,100,0))>0)
	{
		str[t]='\0';
		strcpy(current_ip,str);
	}
	for(int i=0;i<1000000000;i++){ }
	if((t=recv(s,str,100,0))>0)
        {
		str[t]='\0';
		printf("message from the Public server ....%s\n",str);
	}
	printf("Enter any button to exit");
	scanf("%d",&t);
	fp=fopen("freed.txt","a");
	fprintf(fp,"%s\n",current_ip);
	close(s);
	return 0;
}
