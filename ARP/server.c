#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
  int fd, nfd;
  char buff[100], mac[100];

  fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in address;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(1236);
  address.sin_family = AF_INET;

  bind(fd, (struct sockaddr *)&address, sizeof(address));

  listen(fd, 2);

  nfd = accept(fd, NULL, NULL);
  memset(&mac, '\0', sizeof(mac));

  while (1)
  {
    recv(nfd, buff, sizeof(buff), 0);
    printf("received ip address\n");
    char str[80];
    FILE *f = fopen("table.txt", "r");
    if (f)
    {
      while (fgets(str, 80, f) != NULL)
      {
        char *token = strtok(str, " ");
        if (strcmp(token, buff) == 0)
        {
          //printf("%s\n", token);
          token = strtok(NULL, " ");
          strcpy(mac, token);
          break;
        }
        else
          strcpy(mac, "address not found");
      }

      send(nfd, mac, sizeof(mac), 0);
    }
  }
  close(nfd);
}