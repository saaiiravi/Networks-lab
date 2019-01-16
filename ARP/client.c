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
  char buff[100], mac[100];

  fd = socket(AF_INET, SOCK_STREAM, 0);

  memset(&mac, '\0', sizeof(mac));
  memset(&buff, '\0', sizeof(buff));

  struct sockaddr_in address;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(1236);
  address.sin_family = AF_INET;

  connect(fd, (struct sockaddr *)&address, sizeof(address));

  while (1)
  {
    printf("Enter the IP address\n");
    scanf("%s", buff);
    send(fd, buff, sizeof(buff), 0);
    recv(fd, mac, sizeof(mac), 0);
    printf("The corressponding mac address is: %s ", mac);
  }
  close(fd);
}