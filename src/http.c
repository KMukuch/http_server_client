#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http.h"

HTTP_Request_Line* http_create_request_line(char* line)
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
        http_request_line->http_method = http_method_from_string(line, first_space);
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
    http_request_line->http_version = http_version_from_string(second_space + 1);
    
    return http_request_line;
}

HTTP_Status_Line* http_create_status_line(char* line)
{
    
}

HTTP_METHOD http_method_from_string(char* start, char* end)
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

HTTP_VERSION http_version_from_string(char* start)
{
    if(strncmp(start, "HTTP/1.1", 8) == 0)
    {
        return HTTP_VERSION_1_1;
    }

    return HTTP_VERSION_UNDEFINED;
}