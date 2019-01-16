#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(int argc, char *argv[])
{
  int sd;
  char host[100], ip[100];
  struct sockaddr_in server, rns, ans;
  sd = socket(AF_INET, SOCK_DGRAM, 0);

  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[1]));
  int ser = sizeof(server);
  while (1)
  {
    printf("Enter Hostname\n");
    scanf("%s", host);

    sendto(sd, host, sizeof(host), 0, (struct sockaddr *)&server, ser);
    printf("Passing host name to LNS\n");
    recvfrom(sd, ip, sizeof(ip), 0, (struct sockaddr *)&server, &ser);
    if (strcmp(ip, "NOT FOUND") == 0)
    {
      printf("response : %s\n", ip);
      printf("Trying to fetch from RNS\n");
      rns.sin_addr.s_addr = INADDR_ANY;
      rns.sin_family = AF_INET;
      rns.sin_port = htons(atoi(argv[2]));
      sendto(sd, host, sizeof(host), 0, (struct sockaddr *)&rns, ser);
      printf("Passing hostname to RNS..\n");
      recvfrom(sd, ip, sizeof(ip), 0, (struct sockaddr *)&rns, &ser);
      if (strcmp(ip, "NOT FOUND") == 0)
      {
        printf("response : %s", ip);
        printf("Trying to fetch from ans");
        ans.sin_addr.s_addr = INADDR_ANY;
        ans.sin_family = AF_INET;
        ans.sin_port = htons(atoi(argv[3]));
        sendto(sd, host, sizeof(host), 0, (struct sockaddr *)&ans, ser);
        printf("Passing hostname to ANS..\n");
        recvfrom(sd, ip, sizeof(ip), 0, (struct sockaddr *)&ans, &ser);
      }
    }
    printf("%s is its ip", ip);
  }
  return 0;
}