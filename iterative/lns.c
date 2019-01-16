#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  printf("Running in port %d\n", atoi(argv[1]));
  printf("Hello lns\n");
  char host[100], addr[100];

  int sd1;
  sd1 = socket(AF_INET, SOCK_DGRAM, 0);
  char hn[5][20] = {"google", "yahoo", "facebook"};
  char ip[5][30] = {"1.1.1.1", "2.2.2.2", "3.3.3.3"};
  struct sockaddr_in server;

  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[1]));

  bind(sd1, (struct sockaddr *)&server, sizeof(server));

  int ser = sizeof(server);
  while (1)
  {
    recvfrom(sd1, host, sizeof(host), 0, (struct sockaddr *)&server, &ser);
    //./int i;
    strcpy(addr, "");
    for (int i = 0; i < 3; i++)

      if (strcmp(host, hn[i]) == 0)
      {
        printf("response from lns..\n");
        fflush(stdout);
        strcpy(addr, ip[i]);
        break;
      }
  }

  if (strcmp(addr, "") == 0)
  {
    printf("Host name not found in lns\n");
    strcpy(addr, "NOT FOUND");
  }
  sendto(sd1, addr, sizeof(addr), 0, (struct sockaddr *)&server, ser);

  return 0;
}