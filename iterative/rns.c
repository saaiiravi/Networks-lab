#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  printf("Running on port %d\n", atoi(argv[1]));
  int sd1;
  char addr[100], host[100];
  char hn[5][20] = {"hotmail", "orkut", "leetcode"};
  char ip[5][30] = {"5.5.5.5", "6.6.6.6", "7.7.7.7"};
  sd1 = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in server;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[1]));

  bind(sd1, (struct sockaddr *)&server, sizeof(server));
  int ser = sizeof(server);
  while (1)
  {
    recvfrom(sd1, host, sizeof(host), 0, (struct sockaddr *)&server, ser);
    strcpy(addr, " ");
    for (int i = 0; i < 3; i++)
    {
      if (strcmp(host, hn[i]) == 0)
      {
        printf("Response from rns\n");
        strcpy(addr, ip);
        fflush(stdout);
        break;
      }
    }
  }
  if (strcmp(addr, "") == 0)
  {
    printf("ip not found in rns\n");
    strcpy(addr, "NOT FOUND");
    }
  sendto(sd1, addr, sizeof(addr), 0, (struct sockaddr *)&server, &ser);

  return 0;
}