#include "utils.h"

char *getTrimmedLine(char *line)
{
    char *trimmed_line = line;
    while (*trimmed_line == ' ' || *trimmed_line == '\t')
    {
        trimmed_line++;
    }
    return trimmed_line;
}
