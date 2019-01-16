#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main()
{
  int fd;
  char str[100];
  fd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&str, '\0', sizeof(str));

  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(1236);

  connect(fd, (struct sockaddr *)&address, sizeof(address));

  recv(fd, str, sizeof(str), 0);
  //printf("Your local ip is: \n");
  printf("%s", str);

  close(fd);
}