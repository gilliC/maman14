#include "utils.h"
#include <string.h>
#include <stdlib.h>

char *getTrimmedLine(char *line)
{
    char *trimmed_line = line;
    while (*trimmed_line == ' ' || *trimmed_line == '\t')
    {
        trimmed_line++;
    }
    return trimmed_line;
}

char *getStringCleaned(char *str)
{
    char *trimmed_line = str;
    char *end;
    while (*trimmed_line == ' ' || *trimmed_line == '\t')
    {
        trimmed_line++;
    }
    end = trimmed_line + strlen(trimmed_line) - 1;
    while (end > trimmed_line && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
    {
        *end = '\0';
        end--;
    }
    return trimmed_line;
}

int writeInFile(char *str, FILE *file)
{
    printf("writeInFile: %s\n", str);
    fputs(str, file);
    if (str[strlen(str) - 1] != '\n')
    {
        fputs("\n", file);
    }
    return 0;
}
