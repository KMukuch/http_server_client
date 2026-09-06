#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

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

typedef struct HTTP_Start_Line
{
    HTTP_METHOD http_method;
    char *request_target;
    HTTP_VERSION http_version;
} HTTP_Start_Line;

typedef struct HTTP_Mesasge
{
    HTTP_Start_Line http_start_line;
    // headers (fields)
    // body

} HTTP_Mesasge;

HTTP_Start_Line* create_http_start_line(char* line);

HTTP_METHOD parse_http_method(char* start, char* end);

HTTP_VERSION parse_http_version(char* start);

char** line_parser(char* buffer, int len);

int line_counter(char* buffer, int len);

#endif