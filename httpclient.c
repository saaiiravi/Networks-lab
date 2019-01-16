#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
  int clientfd;
  clientfd = socket(AF_INET, SOCK_STREAM, 0);
  char bm[1024] = {0};
  char bu[1024] = {0};
  char bd[1024] = {0};
  char br[1024] = {0};

  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(1234);

  connect(clientfd, (struct sockaddr *)&address, sizeof(address));
  while (1)
  {

    printf("Enter GET PUT POST or DELETE");
    scanf("%s", bm);

    printf("\n Enter file's url ");
    scanf("%s", bu);

    if ((strcmp(bm, "PUT") == 0) || (strcmp(bm, "POST") == 0))
    {
      printf("Enter message to write on file for %s ", bm);
      scanf("%s", bd);
    }

    send(clientfd, bm, sizeof(bm), 0); //method

    send(clientfd, bu, sizeof(bu), 0); //URL

    send(clientfd, bd, sizeof(bd), 0); //message

    recv(clientfd, br, sizeof(br), 0);
    printf("\n");

    printf("%s\n", br);
    printf("Method Executed\n");
  }
  return 0;
}