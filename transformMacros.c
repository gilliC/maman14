#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transformMacros.h"
#include "utils.h"

int isMacroDefinition(char *line, char *macro_name)
{
    char *name_start;
    int i = 0;
    char *trimmed_line = getTrimmedLine(line);

    if (strncmp(trimmed_line, "mcro", 4) == 0)
    {
        if (trimmed_line[4] == ' ' || trimmed_line[4] == '\t')
        {
            name_start = trimmed_line + 4;
            while (*name_start == ' ' || *name_start == '\t')
            {
                name_start++;
            }

            while (name_start[i] != '\0' && name_start[i] != ' ' && name_start[i] != '\t' && name_start[i] != '\n')
            {
                macro_name[i] = name_start[i];
                i++;
            }
            macro_name[i] = '\0';
            return 0;
        }
    }

    return 1;
}

int isMacroEnd(char *line)
{
    char *trimmed_line = getTrimmedLine(line);

    if (strncmp(trimmed_line, "mcroend", 7) == 0)
    {
        if (trimmed_line[7] == ' ' || trimmed_line[7] == '\t' || trimmed_line[7] == '\n' || trimmed_line[7] == '\0')
        {
            return 0;
        }
    }

    return 1;
}

int isValidMacroName(char *name)
{
    int i;
    char *trimmed_name = getStringCleaned(name);

    if (name == NULL || name[0] == '\0')
    {
        return 0;
    }

    for (i = 0; trimmed_name[i] != '\0'; i++)
    {
        if (!((trimmed_name[i] >= 'a' && trimmed_name[i] <= 'z') || trimmed_name[i] == '_'))
        {
            return 0;
        }
    }

    return 1;
}

int validateLine(char *line, char errors[100][100], int *error_count)
{
    if (strlen(line) > LINE_LENGTH)
    {
        sprintf(errors[*error_count], "Line too long (exceeds %d characters)", LINE_LENGTH);
        (*error_count)++;
        return 1;
    }
    return 0;
}

int handleInsideMacro(char *line, char errors[100][100], int *error_count, MacroList *macro_list, int *inside_macro, char *macro_name)
{
    if (isMacroEnd(line) == 0)
    {
        *inside_macro = 0;
    }
    else
    {
        if (addCodeLine(macro_list, macro_name, line) != 0)
        {
            sprintf(errors[*error_count], "Failed to add code line to macro '%s'", macro_name);
            (*error_count)++;
            return 1;
        }
    }
    return 0;
}

int handleMacroDefinition(char *line, char errors[100][100], int *error_count, MacroList *macro_list, int *inside_macro, char *macro_name)
{
    if (isValidMacroName(macro_name))
    {
        if (createNewMacro(macro_list, macro_name) == 0)
        {
            *inside_macro = 1;
        }
        else
        {
            sprintf(errors[*error_count], "Failed to create macro '%s'", macro_name);
            (*error_count)++;
            return 1;
        }
    }
    else
    {
        sprintf(errors[*error_count], "Invalid macro name: %s", macro_name);
        (*error_count)++;
        return 1;
    }
    return 0;
}

int shouldWriteMacroCode(char *line, MacroList *macro_list)
{
    if (getCodeByName(macro_list, line) != NULL)
    {
        return 0;
    }
    return 1;
}

int writeMacroCode(char *line, char errors[100][100], int *error_count, MacroList *macro_list, FILE *output_file)
{
    int i;
    char **codeList = getCodeByName(macro_list, line);
    if (codeList != NULL)
    {
        for (i = 0; codeList[i] != NULL; i++)
        {
            if (codeList[i] != NULL && codeList[i][0] != '\0')
            {
                writeInFile(codeList[i], output_file);
            }
        }
        return 0;
    }
    else
    {
        sprintf(errors[*error_count], "Macro '%s' not found", line);
        (*error_count)++;
        return 1;
    }
    return 0;
}

int transformMacros(char *filename, char errors[100][100])
{
    char input_filename[FILE_NAME_LENGTH];
    char output_filename[FILE_NAME_LENGTH];
    FILE *input_file;
    FILE *output_file;
    char line[LINE_LENGTH];
    int result = 0;
    int error_count = 0;
    /* todo - make this dynamic and no hardocded values*/
    /*  char errors[100][100]; */
    char macro_name[LINE_LENGTH - MACRO_NAME_DEFINITION_LENGTH];
    int inside_macro = 0;
    MacroList *macro_list;
    int i;

    macro_list = createMacroList();
    if (macro_list == NULL)
    {
        strcpy(errors[error_count], "Failed to create macro list");
        printf("Failed to create macro list\n");
        error_count++;
        return 1;
    }

    strcpy(input_filename, filename);
    strcat(input_filename, ".txt");

    strcpy(output_filename, filename);
    strcat(output_filename, ".am");

    input_file = fopen(input_filename, "r");
    if (input_file == NULL)
    {
        printf("File '%s' not found\n", filename);
        onFinish(macro_list);
        return 1;
    }

    output_file = fopen(output_filename, "w");
    if (output_file == NULL)
    {
        printf("File '%s' cannot be created \n", filename);
        fclose(input_file);
        onFinish(macro_list);
        return 1;
    }

    while (fgets(line, sizeof(line), input_file))
    {
        if (validateLine(line, errors, &error_count) != 0)
        {
            result = 1;
        }
        /* if inside macro, add code line to macro */
        else if (inside_macro != 0)
        {
            if (handleInsideMacro(line, errors, &error_count, macro_list, &inside_macro, macro_name) != 0)
            {
                result = 1;
            }
        }
        else if (shouldWriteMacroCode(line, macro_list) == 0)
        {
            if (writeMacroCode(line, errors, &error_count, macro_list, output_file) != 0)
            {
                result = 1;
            }
        }
        /* if macro definition, create new macro */
        else if (isMacroDefinition(line, macro_name) == 0)
        {
            if (handleMacroDefinition(line, errors, &error_count, macro_list, &inside_macro, macro_name) != 0)
            {
                result = 1;
            }
        }
        else
        {
            writeInFile(line, output_file);
        }
    }

    fclose(input_file);
    fclose(output_file);

    onFinish(macro_list);

    if (result == 1)
    {
        printf("Found %d errors while transforming macros\n", error_count);
        for (i = 0; i < error_count; i++)
        {
            printf("error[%d]: %s\n", i, errors[i]);
        }
        remove(output_filename);
    }

    return result;
}
