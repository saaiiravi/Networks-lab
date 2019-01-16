#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
  int fd, nfd, cp, done;
  char buff[100];

  fd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&buff, '\0', sizeof(buff));

  struct sockaddr_in addr;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1236);

  bind(fd, (struct sockaddr *)&addr, sizeof(addr));

  listen(fd, 5);

  while (1)
  {
    nfd = accept(fd, NULL, NULL);
    if (accept > 0)
      printf("accepted\n");
    cp = fork();
    if (cp < 0)
      perror("fork error");
    else if (cp == 0)
    {
      done = 0;
      do
      {
        strcpy(buff, "child process created");
        send(nfd, buff, sizeof(buff), 0);
      } while (!done);
    }
  }
}