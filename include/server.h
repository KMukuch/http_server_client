#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>

int init_server();

int accept_client(int server_fd);

int recv_server(int fd, char* buffer, int len);

int close_server_client(int* fd_array, int len);

#endif