#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
  int sock_id;
  char buff[100];
  struct sockaddr_in server;
  memset(&server, 0, sizeof(server));

  sock_id = socket(AF_INET, SOCK_STREAM, 0);

  server.sin_port = htons(3008);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;

  int c_stat = bind(sock_id, (struct sockaddr *)&server, sizeof(server));
  if (c_stat == -1)
  {
    printf("error in binding");
  }
  listen(sock_id, 5);
  int temp_sock = accept(sock_id, NULL, NULL);

  while (1)
  {
    recv(temp_sock, buff, 100, 0);
    printf("Client: %s", buff);
    printf("you:");
    fgets(buff, 100, stdin);
    if (strncmp(buff, "bye", 3) == 0)
      break;
    send(temp_sock, buff, 100, 0);
  }
  close(temp_sock);

  return 0;
}