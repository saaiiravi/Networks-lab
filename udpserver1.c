#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

int main()
{
  int sockfd, clen;
  char buff[256];
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in servaddr, clientaddr;

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&clientaddr, 0, sizeof(clientaddr));

  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(7000);

  bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  clen = sizeof(servaddr);

  while (1)
  {
    recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&servaddr, &clen);
    printf("Client : %s", buff);
    printf("You : ");
    scanf("%s", buff);
    if (strcmp(buff, "bye") == 0)
      break;
    sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&servaddr, clen);
  }
  close(sockfd);
}