#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "datagram.h"

int main()
{
  int fd, nfd, cp, done;
  char buff[100];
  struct datagram data = {"sai", 1234, "saaii@gmail.com"};

  fd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&buff, '\0', sizeof(buff));

  struct sockaddr_in addr;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1237);

  bind(fd, (struct sockaddr *)&addr, sizeof(addr));

  listen(fd, 5);

  nfd = accept(fd, NULL, NULL);
  int ad = sizeof(addr);
  sendto(nfd, &data, sizeof(data), 0, (struct sockaddr *)&addr, ad);
  printf("data sent\n");
  close(fd);
}