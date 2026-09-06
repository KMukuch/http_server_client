#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>

int server_init();

int server_accept_client(int server_fd);

int server_recv(int fd, char* buffer, int len);

int server_close_fds(int* fd_array, int len);

#endif