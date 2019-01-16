#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
  int sock_fd;
  char buff[100];
  struct sockaddr_in client;

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  client.sin_port = htons(3008);
  client.sin_family = AF_INET;
  client.sin_addr.s_addr = INADDR_ANY;

  connect(sock_fd, (struct sockaddr *)&client, sizeof(client));

  while (1)
  {
    printf("You:");
    fgets(buff, 100, stdin);
    if (strncmp(buff, "bye", 3) == 0)
      break;
    send(sock_fd, buff, 100, 0);
    recv(sock_fd, buff, 100, 0);
    printf("Client : %s", buff);
  }
  close(sock_fd);

  return 0;
}