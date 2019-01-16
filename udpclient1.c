#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
  int clifd, csize;
  char buff[200];
  clifd = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in cliaddr;
  memset(&cliaddr, 0, sizeof(cliaddr));

  cliaddr.sin_addr.s_addr = INADDR_ANY;
  cliaddr.sin_port = htons(7000);
  cliaddr.sin_family = AF_INET;

  csize = sizeof(cliaddr);

  while (1)
  {
    printf("you: ");
    scanf("%s", buff);
    if (strcmp(buff, "bye") == 0)
      break;
    sendto(clifd, buff, sizeof(buff), 0, (struct sockaddr *)&cliaddr, csize);
    recvfrom(clifd, buff, sizeof(buff), 0, (struct sockaddr *)&cliaddr, &csize);
    printf("server : %s", buff);
  }
  close(clifd);
}
