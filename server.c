#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
  char server_message[] = "Hello from server";
  int socket_server;
  socket_server = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server_address;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(3000);
  server_address.sin_family = AF_INET;

  bind(socket_server, (struct sockaddr *)&server_address, sizeof(server_address));

  listen(socket_server, 5);

  int client_socket;
  client_socket = accept(socket_server, NULL, NULL);

  send(client_socket, server_message, sizeof(server_message), 0);

  return 0;
}