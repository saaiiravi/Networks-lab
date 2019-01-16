#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
  int client_socket;
  client_socket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in address;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_family = AF_INET;
  address.sin_port = htons(3000);

  int connection_status = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
  if (connection_status == -1)
    printf("error in econnection");

  char response[256];
  recv(client_socket, &response, sizeof(response), 0);

  printf("The data sent by the server %s", response);

  close(client_socket);
}