#include <stdio.h>
#include <string.h>
#include "server.h"
#include "parser.h"

#define MAX_BUFFER 1024

int main(int argc, char *argv[])
{
    int server_fd = init_server();
    int client_fd = accept_client(server_fd);

    int fd_array[] = {server_fd, client_fd};

    char buffer[MAX_BUFFER];
    int bytes_read = recv_server(client_fd, buffer, MAX_BUFFER);
    
    char **lines = line_parser(buffer, bytes_read);
    
    for(int i = 0; i < line_counter(buffer, bytes_read); i++)
    {
        printf("%s\n", lines[i]);
    }

    close_server_client(fd_array, 2);

    return 1;
}