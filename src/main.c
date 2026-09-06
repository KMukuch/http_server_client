#include <stdio.h>
#include <string.h>
#include "server.h"
#include "parser.h"
#include "http.h"

#define MAX_BUFFER 1024

int main(int argc, char *argv[])
{
    int server_fd = server_init();
    int client_fd = server_accept_client(server_fd);

    int fd_array[] = {server_fd, client_fd};

    char buffer[MAX_BUFFER];
    int bytes_read = server_recv(client_fd, buffer, MAX_BUFFER);
    
    char **lines = parser_parse_line(buffer, bytes_read);
    HTTP_Request_Line *http_request_line = http_create_request_line(lines[0]);
    
    for(int i = 0; i < parser_line_counter(buffer, bytes_read); i++)
    {
        printf("%s\n", lines[i]);
    }
    printf("%i %s %i\n", http_request_line->http_method, http_request_line->request_target, http_request_line->http_version);

    server_close_fds(fd_array, 2);

    return 1;
}