#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

char** parser_parse_line(char* buffer, int len);

int parser_line_counter(char* buffer, int len);

#endif