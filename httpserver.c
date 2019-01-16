#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>

int main()
{
  int server_fd, new_socket;
  char bm[1024] = {0};
  char bu[1024] = {0};
  char bd[1024] = {0};

  server_fd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in address;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_family = AF_INET;
  address.sin_port = htons(1234);

  bind(server_fd, (struct sockaddr *)&address, sizeof(address));

  listen(server_fd, 3);

  new_socket = accept(server_fd, NULL, NULL);

  while (1)
  {

    recv(new_socket, bm, sizeof(bm), 0);
    recv(new_socket, bu, sizeof(bu), 0);
    recv(new_socket, bd, sizeof(bd), 0);

    if (strcmp(bm, "GET") == 0)
    {
      printf("GET\n");
      char *buff = 0;
      long length;
      FILE *fp = fopen(bu, "rb");
      if (fp)

      {
        //printf("fp\n");
        fseek(fp, 0, SEEK_END);
        length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        buff = malloc(length);
        if (buff)
          fread(buff, 1, length, fp);
        fclose(fp);
      }
      send(new_socket, buff, strlen(buff), 0);
      printf("File contents sent\n");
    }

    else if (strcmp(bm, "PUT") == 0)
    {
      printf("PUT\n");
      char message[] = "FIle contents updated";
      FILE *fp = fopen(bu, "w");
      if (fp == NULL)
        printf("error");
      fprintf(fp, "%s", bd);
      fclose(fp);
      send(new_socket, message, sizeof(message), 0);
    }
    else if (strcmp(bm, "POST") == 0)
    {
      char message[] = "FIle contents updated";
      FILE *fp = fopen(bu, "w");
      if (fp == NULL)
        printf("error");
      fprintf(fp, "%s", bd);
      fclose(fp);
      send(new_socket, message, sizeof(message), 0);
    }
    else if (strcmp(bm, "DEL") == 0)
    {
      printf("DELETE\n");
      char message[] = "FILE DELETED";
      FILE *d = fopen(bu, "w");
      if (remove(bu) == 0)
        printf("Removed sucessfully\n");
      send(new_socket, message, sizeof(message), 0);
    }
  }

  close(new_socket);

  return 0;
}
