#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main(void)
{
	int s,s2,t,len,cp;
	struct sockaddr_in local,rem;
	char str[100],str1[100];
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		perror("socket");
		exit(1);
	}
	bzero((char *)&local,sizeof(local));
	local.sin_family=AF_INET;
	local.sin_port=htons(3000);
	local.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(bind(s,(struct sockaddr *)&local,sizeof(local))==-1)
	{
		perror("bind");
		exit(1);
	}
	while(1){
		printf("Listening on port - 3000\n");
		if(listen(s,10)==-1)
		{
			perror("listen");
			exit(1);
		}
		int n;
		t=sizeof(rem);
		s2=accept(s,(struct sockaddr *)&rem,&t);
		if(s2==-1)
		{
			perror("accept");
			exit(1);
		}
		printf("Sending Packets \n");
		if((t=recv(s2,str,100,0))>0)
		{
			str[t]='\0';
			printf("Recieving packets from .. %s\n",str);
		}
		strcpy(str1,"Hello !!.. ");
		strcat(str1,str);
		if(send(s2,str1,sizeof(str1),0)<0)		
		{
			perror("send");
		}
		close(s2);
	}
	return 0;
}
