#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

HTTP_Request_Line* create_http_request_line(char* line)
{
    HTTP_Request_Line *http_request_line = calloc(1, sizeof(HTTP_Request_Line));
    if(!http_request_line)
    {
        return NULL;
    }

    int start_pos = 0;
    int line_index = 0;
    
    char *first_space = strchr(line, ' ');
    if(!first_space)
    {
        free(http_request_line);
        return NULL;
    }
    else
    {
        http_request_line->http_method = parse_http_method(line, first_space);
    }

    char *second_space = strchr(first_space + 1, ' ');
    if(!second_space)
    {
        free(http_request_line);

        return NULL;
    }
    else
    {
        http_request_line->request_target = calloc(second_space - first_space, sizeof(char));
        if(!http_request_line->request_target)
        {
            free(http_request_line);

            return NULL;
        }

        strncpy(http_request_line->request_target, first_space + 1, second_space - first_space - 1);

        http_request_line->request_target[second_space - first_space - 1] = '\0';
    }
    http_request_line->http_version = parse_http_version(second_space + 1);
    
    return http_request_line;
}

HTTP_METHOD parse_http_method(char* start, char* end)
{
    int len = end - start;
    if(strncmp(start, "GET", len) == 0)
    {
        return HTTP_METHOD_GET;
    }
    else if(strncmp(start, "POST", len) == 0)
    {
        return HTTP_METHOD_POST;
    }
    else if(strncmp(start, "PUT", len) == 0)
    {
        return HTTP_METHOD_PUT;
    }
    else if(strncmp(start, "DELETE", len) == 0)
    {
        return HTTP_METHOD_DELETE;
    }
    else if(strncmp(start, "HEAD", len) == 0)
    {
        return HTTP_METHOD_HEAD;
    }
    else if(strncmp(start, "OPTIONS", len) == 0)
    {
        return HTTP_METHOD_OPTIONS;
    }
    else if(strncmp(start, "CONNECT", len) == 0)
    {
        return HTTP_METHOD_CONNECT;
    }
    else if(strncmp(start, "TRACE", len) == 0)
    {
        return HTTP_METHOD_TRACE;
    }

    return HTTP_METHOD_UNDEFINED;
}

HTTP_VERSION parse_http_version(char* start)
{
    if(strncmp(start, "HTTP/1.1", 8) == 0)
    {
        return HTTP_VERSION_1_1;
    }

    return HTTP_VERSION_UNDEFINED;
}

char** line_parser(char* buffer, int len)
{
    char **lines;
    int lines_count = line_counter(buffer, len);
    int start_pos = 0;
    int line_index = 0;

    if(lines_count > 0)
    {
        lines = calloc(lines_count, sizeof(char *));
        for(int i = 1; i < len; i++)
        {
            if(buffer[i-1] == '\r' && buffer[i] == '\n')
            {
                char* line = calloc(i - start_pos + 1, sizeof(char));
                if(!line)
                {
                    perror("calloc");

                    return NULL;
                }

                memcpy(line, buffer + start_pos, i - start_pos);
                line[i - start_pos] = '\0';

                lines[line_index] = line;
                line_index++;

                start_pos = i +1;
            }
        }

        return lines;
    }

    return NULL;
}

int line_counter(char* buffer, int len)
{
    if(len < 0)
    {
        return 0;
    }
    
    int counter = 0;
    for(int i = 1; i < len; i++)
    {
        if(buffer[i-1] == '\r' && buffer[i] == '\n')
        {
            counter++;
        }
    }

    return counter;
}