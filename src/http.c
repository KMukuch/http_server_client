#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http.h"

HTTP_Request_Message* http_create_request_message(char* buffer, char** lines, int count, int bytes_read)
{
    HTTP_Request_Message *http_request_message = calloc(1, sizeof(HTTP_Request_Message));
    if(!http_request_message)
    {
        return NULL;
    }

    if(!lines)
    {
        free(http_request_message);

        return NULL;
    }

    if(!http_create_request_line(lines[0], &http_request_message->http_request_line))
    {
        free(http_request_message);

        return NULL;
    }

    http_request_message->http_field_line_array = calloc(count - 1, sizeof(HTTP_Field_Line));
    if(!http_request_message->http_field_line_array)
    {
        free(http_request_message);

        return NULL;
    }

    for(int i = 1; i < count; i++)
    {
        if(!http_create_field_line(lines[i], &http_request_message->http_field_line_array[i - 1]))
        {
            free(http_request_message);
         
            return NULL;
        }
    }

    return http_request_message;
}

HTTP_Response_Message* http_create_response_message(HTTP_Request_Message* http_request_message)
{
    HTTP_Response_Message *http_response_message = calloc(1, sizeof(HTTP_Response_Message));
    if(!http_response_message)
    {
        return NULL;
    }

    if(!http_create_status_line(&http_request_message->http_request_line, &http_response_message->http_status_line))
    {
        free(http_response_message);
        
        return NULL;
    }

    return http_response_message;
}

int http_create_request_line(char* line, HTTP_Request_Line *http_request_line)
{
    if(!http_request_line)
    {
        return 0;
    }

    char *first_space = strchr(line, ' ');
    if(!first_space)
    {
        return 0;
    }
    else
    {
        http_request_line->http_method = http_method_from_string(line, first_space);
    }

    char *second_space = strchr(first_space + 1, ' ');
    if(!second_space)
    {
        return 0;
    }
    else
    {
        http_request_line->request_target = calloc(second_space - first_space, sizeof(char));
        if(!http_request_line->request_target)
        {
            return 0;
        }

        strncpy(http_request_line->request_target, first_space + 1, second_space - first_space - 1);

        http_request_line->request_target[second_space - first_space - 1] = '\0';
    }
    http_request_line->http_version = http_version_from_string(second_space + 1);
    
    return 1;
}

int http_create_status_line(HTTP_Request_Line *http_request_line, HTTP_Status_Line *http_status_line)
{
    if(!http_request_line || !http_status_line)
    {
        return 0;
    }

    http_status_line->http_version = http_request_line->http_version;
    http_status_line->status_code = HTTP_STATUS_CODE_NOT_IMPLEMENTED;
    http_status_line->reason_phrase = "Not Implemented";

    return 1;
}

int http_create_field_line(char *line, HTTP_Field_Line *http_field_line)
{
    if(!http_field_line)
    {
        return 0;
    }

    http_field_line->field_name = http_field_name_from_string(line);
    if(!http_field_line->field_name)
    {
        return 0;
    }
    http_field_line->field_value = http_field_value_from_string(line);

    return 1;
}

HTTP_METHOD http_method_from_string(char* start, char* end)
{
    int len = end - start;

    if(len == 3 && strncmp(start, "GET", 3) == 0)
    {
        return HTTP_METHOD_GET;
    }
    else if(len == 4 && strncmp(start, "POST", 4) == 0)
    {
        return HTTP_METHOD_POST;
    }
    else if(len == 3 && strncmp(start, "PUT", 3) == 0)
    {
        return HTTP_METHOD_PUT;
    }
    else if(len == 6 && strncmp(start, "DELETE", 6) == 0)
    {
        return HTTP_METHOD_DELETE;
    }
    else if(len == 4 && strncmp(start, "HEAD", 4) == 0)
    {
        return HTTP_METHOD_HEAD;
    }
    else if(len == 7 && strncmp(start, "OPTIONS", 7) == 0)
    {
        return HTTP_METHOD_OPTIONS;
    }
    else if(len == 7 && strncmp(start, "CONNECT", 7) == 0)
    {
        return HTTP_METHOD_CONNECT;
    }
    else if(len == 5 && strncmp(start, "TRACE", 5) == 0)
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

char* http_field_name_from_string(char* line)
{
    char* field_name;
    char *separator = strchr(line, ':');
    if(!separator)
    {
        return NULL;
    }
    if(separator == line)
    {
        return NULL;
    }
    if(*(separator - 1) == ' ')
    {
        return NULL;
    }

    field_name = calloc(separator - line + 1, sizeof(char));
    if(!field_name)
    {
        return NULL;
    }
    memcpy(field_name, line, separator - line);
    field_name[separator - line] = '\0';

    return field_name;
}

char* http_field_value_from_string(char* line)
{
    char* field_value;
    char *separator = strchr(line, ':');
    if(!separator)
    {
        return NULL;
    }
    if(separator == line)
    {
        return NULL;
    }
    if(*(separator - 1) == ' ')
    {
        return NULL;
    }

    if(*(separator + 1) == ' ')
    {
        field_value = calloc(strlen(separator + 2) + 1, sizeof(char));
        if(!field_value)
        {
            return NULL;
        }

        strcpy(field_value, separator + 2);
    }
    else
    {
        field_value = calloc(strlen(separator + 1) + 1, sizeof(char));
        if(!field_value)
        {
            return NULL;
        }

        strcpy(field_value, separator + 1);
    }

    return field_value;
}

char *http_version_to_string(HTTP_VERSION http_version)
{
    if(http_version == HTTP_VERSION_1_1)
    {
        return "HTTP/1.1";
    }

    return NULL;
}

int http_serialize_message(char *buffer, int len, HTTP_Response_Message *http_response_message)
{
    if(!http_response_message)
    {
        return 0;
    }

    return snprintf(buffer, len,"%s %d %s\r\n", http_version_to_string(http_response_message->http_status_line.http_version), http_response_message->http_status_line.status_code, http_response_message->http_status_line.reason_phrase);
}