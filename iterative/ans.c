#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  printf("Running on port %d\n", atoi(argv[1]));
  int sd1;
  char host[100], addr[100];
  char hn[10][20] = {"google", "yahoo", "facebook", "hotmail", "orkut", "leetcode", "chronus", "nutonix", "amazon", "samsung"};
  char ip[10][30] = {"1.1.1.1", "2.2.2.2", "3.3.3.3", "5.5.5.5", "6.6.6.6", "7.7.7.7", "8.8.8.8", "9.9.9.9", "10.10.10.10", "11.11.11.11"};
  sd1 = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in server;
  server.sin_port = htons(atoi(argv[1]));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  bind(sd1, (struct sockaddr *)&server, sizeof(server));

  int ser = sizeof(server);
  while (1)
  {
    recvfrom(sd1, host, sizeof(host), 0, (struct sockaddr *)&server, ser);
    strcpy(addr, "404 error: NOT FOUND");
    for (int i = 0; i < 10; i++)
    {
      if (strcmp(host, hn[i]) == 0)
      {
        printf("Response from ans\n");
        strcpy(addr, ip);
        fflush(stdout);
        break;
      }
    }
  }
  sendto(sd1, addr, sizeof(addr), 0, (struct sockaddr *)&server, &ser);

  return 0;
}