#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "datagram.h"

int main()
{
  int client_socket;
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  struct datagram clientdata;

  struct sockaddr_in address;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_family = AF_INET;
  address.sin_port = htons(1237);

  int connection_status = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
  if (connection_status == -1)
    printf("error in econnection");
  int adr = sizeof(address);

  recvfrom(client_socket, &clientdata, sizeof(clientdata), 0, (struct sockaddr *)&address, &adr);
  printf("Data recieved is\n Name:%s \n Register Number : %ld  \n Mail : %s\n", clientdata.name, clientdata.regno, clientdata.mail);
}