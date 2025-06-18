#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transformMacros.h"

int transformMacros(char *filename, char errors[100][100])
{
    char input_filename[FILE_NAME_LENGTH];
    char output_filename[FILE_NAME_LENGTH];
    FILE *input_file;
    FILE *output_file;
    char line[LINE_LENGTH];
    int response = 0;
    int error_count = 0;
    /* todo - make this dynamic and no hardocded values*/
    /*  char errors[100][100]; */

    strcpy(input_filename, filename);
    strcat(input_filename, ".txt");

    strcpy(output_filename, filename);
    strcat(output_filename, ".am");

    input_file = fopen(input_filename, "r");
    if (input_file == NULL)
    {
        printf("File '%s' not found\n", filename);
        return 1;
    }

    output_file = fopen(output_filename, "w");
    if (output_file == NULL)
    {
        printf("File '%s' cannot be created \n", filename);
        fclose(input_file);
        return 1;
    }

    while (fgets(line, sizeof(line), input_file))
    {
        if (strlen(line) > LINE_LENGTH)
        {
            sprintf(errors[error_count], "Line too long (exceeds %d characters)", LINE_LENGTH);
            error_count++;
            response = 1;
        }
        else
        {
            fputs(line, output_file);
        }
    }

    fclose(input_file);
    fclose(output_file);

    if (response == 1)
    {
        remove(output_filename);
    }

    return response;
}
