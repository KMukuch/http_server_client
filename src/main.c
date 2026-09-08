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
    int count = parser_line_counter(buffer, bytes_read);

    HTTP_Request_Message *http_request_message = http_create_request_message(buffer, lines, count, bytes_read);
    
    HTTP_Response_Message *http_response_message = http_create_response_message(http_request_message);

    bytes_read = http_serialize_message(buffer, MAX_BUFFER, http_response_message);
    server_send(client_fd, buffer, bytes_read);

    server_close_fds(fd_array, 2);

    return 1;
}