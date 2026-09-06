#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

typedef enum HTTP_STATUS_CODE
{
    HTTP_STATUS_CODE_OK = 200,
    HTTP_STATUS_CODE_BAD_REQUEST = 400,
    HTTP_STATUS_CODE_NOT_FOUND = 404,
    HTTP_STATUS_CODE_INTERNAL_SERVER_ERROR = 500
} HTTP_STATUS_CODE;

typedef enum HTTP_METHOD
{
    HTTP_METHOD_UNDEFINED,
    HTTP_METHOD_GET,
    HTTP_METHOD_POST,
    HTTP_METHOD_PUT,
    HTTP_METHOD_DELETE,
    HTTP_METHOD_HEAD,
    HTTP_METHOD_OPTIONS,
    HTTP_METHOD_CONNECT,
    HTTP_METHOD_TRACE
} HTTP_METHOD;

typedef enum HTTP_VERSION
{
    HTTP_VERSION_UNDEFINED,
    HTTP_VERSION_1_1
} HTTP_VERSION;

typedef struct HTTP_Request_Line
{
    HTTP_METHOD http_method;
    char *request_target;
    HTTP_VERSION http_version;
} HTTP_Request_Line;

typedef struct HTTP_Status_Line
{
    HTTP_VERSION http_version;
    HTTP_STATUS_CODE status_code;
    char *reason_phrase;
} HTTP_Status_Line;

typedef struct HTTP_Field_Line
{
    char *field_name;
    char *field_value;
} HTTP_Field_Line;

typedef struct HTTP_Request_Message
{
    HTTP_Request_Line http_request_line;
    HTTP_Field_Line *http_field_line_array;
} HTTP_Request_Message;

typedef struct HTTP_Response_Message
{
    HTTP_Status_Line http_status_line;
    HTTP_Field_Line *http_field_line_array;
    char *message_body;
} HTTP_Response_Message;

HTTP_Request_Line* create_http_request_line(char* line);

HTTP_METHOD parse_http_method(char* start, char* end);

HTTP_VERSION parse_http_version(char* start);

char** line_parser(char* buffer, int len);

int line_counter(char* buffer, int len);

#endif