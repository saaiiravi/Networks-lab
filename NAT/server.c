#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main(void)
{
	char default_ip[100];
	strcpy(default_ip,"198.168.0.0\0");
        int s,s2,s3,t,len,cp;
        struct sockaddr_in local,rem,public;
        char str[100];
        printf("Server Running..\n");
	s=socket(AF_INET,SOCK_STREAM,0);
        if(s==-1)
	{
		perror("socket");
		exit(1);
	}
	bzero((char *)&local,sizeof(local));
	local.sin_family=AF_INET;
	local.sin_port=htons(5559);
	local.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(bind(s,(struct sockaddr *)&local,sizeof(local))==-1)
	{
		perror("bind");
		exit(1);
	}
	if(listen(s,5)==-1)
	{
		perror("listen");
		exit(1);
	}
	while(1)
	{
		int done,n;
		t=sizeof(rem);
		s2=accept(s,(struct sockaddr *)&rem,&t);
		if(s2==-1)
		{
			perror("accept");
			exit(1);
		}
		printf("connected \n");
		if((cp=fork())<0)
		{
			perror("fork error");
		}
		else if(cp==0)
		{
			done=0;
			do
			{
				printf("Assigning IP Address\n");
				FILE *fp,*fp2,*fp3,*fp4;
				fp=fopen("natTable.txt","r");
				fp2=fopen("natTable.txt","a");
				fp3=fopen("freed.txt","r");
				fp4=fopen("replica.txt","w");
				if(fp==NULL)	
				{
					printf("Error in Assigning ip");
				}
				else
				{
					if(fp3==NULL||fp4==NULL)
					{
						printf("Error in opening the file");
					}
					else
					{
						char freed[100],freed_count=0,freed_backup[100];
						while(fscanf(fp3,"%s",freed)==1)
						{
							freed_count++;
							if(freed_count==1)
							{
								strcpy(freed_backup,freed);	
							}
							else
							{
								fprintf(fp4,"%s\n",freed);
							}
						}
						fclose(fp3);
						fclose(fp4);
						remove("freed.txt");
						rename("replica.txt","freed.txt");
						char current_ip[100];
						int next_ip=0;
						if(freed_count<1)
						{
							while(fscanf(fp,"%s",current_ip)==1)
							{
								//int dot_count=0;
								int temp_ip=0;
								int flag=0;
								for(int temp=0;current_ip[temp]!='\0';temp++)
								{
									if(current_ip[temp]==':')
									{
										temp++;
										flag=1;
									}
									if(flag==1)
									{
										int t_no=(int)current_ip[temp]-48;
										temp_ip=(temp_ip*10)+t_no;	
									}
								}
								next_ip=temp_ip;
							}
							next_ip++;
							//int dot_count=0;
							int flag=0;
							int temp_ip=0;
							for(int temp=0;current_ip[temp]!='\0';temp++)
							{

								if(flag==1)
								{
									fprintf(fp2,"%d\n",next_ip);
									break;
								}
								else
								{
									fprintf(fp2,"%c",current_ip[temp]);
								}
								if(current_ip[temp]==':')
								{
									flag=1;
								}
							}
							fseek(fp,0,0);
							while(fscanf(fp,"%s",current_ip)==1)
							{
							}
						}
						else
						{
							strcpy(current_ip,freed_backup);
						}
						if(send(s2,current_ip,sizeof(current_ip),0)<0)
						{
							perror("send");
						}
						printf("Contacting the public Domain Server...\n");
						int a;
						for(int z=0;z<1000000;z++){ }
						// Code for Contacting the public Domain 
						s3=socket(AF_INET,SOCK_STREAM,0);
						if(s3==-1)
						{
							perror("socket");
							exit(1);
						}
						public.sin_family=AF_INET;
						public.sin_port=htons(3000);
						public.sin_addr.s_addr=inet_addr("127.0.0.1");
						a=connect(s3,(struct sockaddr *)&public,sizeof(public));
						if(a==-1)
						{
							perror("connect");
							exit(1);
						}
						if(send(s3,current_ip,sizeof(current_ip),0)<0)
						{
							perror("send");
						}	
						if((t=recv(s3,str,100,0))>0)
						{
							str[t]='\0';
							if(send(s2,str,sizeof(str),0)<0)
							{
								perror("send");
							}
						}
						printf("Recieved packets...\n");
						done=1;
					}
				}
				fclose(fp);
				fclose(fp2);
			}while(!done);
			exit(0);
		}
		close(s2);
	}
	return 0;
}

