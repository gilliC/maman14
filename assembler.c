#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transformMacros.h"

int main(int argc, char *argv[])
{
    int i;
    FILE *file;

    if (argc < 2)
    {
        fprintf(stderr, "Missing filename\n");
        return 1;
    }

    for (i = 1; i < argc; i++)
    {
        char filename[FILE_NAME_LENGTH];
        strcpy(filename, argv[i]);
        strcat(filename, ".txt");

        file = fopen(filename, "r");
        if (file != NULL)
        {
            printf("File '%s': SUCCESS - file read\n", argv[i]);
            fclose(file);
        }
        else
        {
            printf("File '%s': FAILURE - cannot read file\n", argv[i]);
        }
    }

    return 0;
}
