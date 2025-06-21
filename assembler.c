#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transformMacros.h"

int main(int argc, char *argv[])
{
    int i;
    FILE *file;
    char errors[100][100];

    if (argc < 2)
    {
        fprintf(stderr, "Missing filename\n");
        return 1;
    }

    for (i = 1; i < argc; i++)
    {
        char filename[FILE_NAME_LENGTH];
        char filename_with_txt[FILE_NAME_LENGTH];
        strcpy(filename, argv[i]);
        strcpy(filename_with_txt, filename);
        strcat(filename_with_txt, ".txt");

        file = fopen(filename_with_txt, "r");
        if (file != NULL)
        {
            printf("File '%s': SUCCESS - file read\n", argv[i]);
            transformMacros(filename, errors);
            fclose(file);
        }
        else
        {
            printf("File '%s': FAILURE - cannot read file\n", argv[i]);
        }
    }

    return 0;
}
