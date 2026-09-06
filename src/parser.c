#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

char** parser_parse_line(char* buffer, int len)
{
    char **lines;
    int lines_count = parser_line_counter(buffer, len);
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

int parser_line_counter(char* buffer, int len)
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