#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

char** line_parser(char* buffer, int len);

int line_counter(char* buffer, int len);

#endif