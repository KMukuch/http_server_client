#include <stdio.h>
#include <string.h>
#include "parser.h"

int main(int argc, char *argv[])
{
    char* buffer = "GET /where?q=now HTTP/1.1\r\nHost: www.example.org\r\n";

    char **lines = line_parser(buffer, strlen(buffer));
    
    for(int i = 0; i < line_counter(buffer, strlen(buffer)); i++)
    {
        printf("%s\n", lines[i]);
    }

    return 1;
}