#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macroDefintions.h"
#include "utils.h"

MacroList *createMacroList(void)
{
    MacroList *list = malloc(sizeof(MacroList));
    list->macros = NULL;
    list->count = 0;
    return list;
}

int createNewMacro(MacroList *list, char *name)
{
    Macro *temp = realloc(list->macros, (list->count + 1) * sizeof(Macro));
    if (temp == NULL)
    {
        fprintf(stderr, "Memory allocation failed for macro '%s'\n", name);
        return 1;
    }
    list->macros = temp;
    list->macros[list->count].name = malloc(strlen(name) + 1);
    if (list->macros[list->count].name == NULL)
    {
        fprintf(stderr, "Memory allocation failed for macro name '%s'\n", name);
        return 1;
    }
    strcpy(list->macros[list->count].name, name);
    list->macros[list->count].code = NULL;
    list->macros[list->count].codeCount = 0;
    list->count++;
    return 0;
}

int addCodeLine(MacroList *list, char *name, char *code)
{
    char **temp;
    int i;
    char *trimmed_code = getTrimmedLine(code);
    for (i = 0; i < list->count; i++)
    {
        if (strcmp(list->macros[i].name, name) == 0)
        {
            temp = realloc(list->macros[i].code, (list->macros[i].codeCount + 1) * sizeof(char *));
            if (temp == NULL)
            {
                fprintf(stderr, "Memory allocation failed for code line in macro '%s'\n", name);
                return 1;
            }
            list->macros[i].code = temp;

            list->macros[i].code[list->macros[i].codeCount] = malloc(strlen(trimmed_code) + 1);
            if (list->macros[i].code[list->macros[i].codeCount] == NULL)
            {
                fprintf(stderr, "Memory allocation failed for code line in macro '%s'\n", name);
                return 1;
            }
            strcpy(list->macros[i].code[list->macros[i].codeCount], trimmed_code);
            list->macros[i].codeCount++;
            return 0;
        }
    }
    fprintf(stderr, "Macro '%s' not found\n", name);
    return 1;
}

char **getCodeByName(MacroList *list, char *name)
{
    int i;
    char *trimmed_name = getStringCleaned(name);
    char **result = NULL;

    if (trimmed_name == NULL)
    {
        return NULL;
    }

    for (i = 0; i < list->count; i++)
    {
        if (strcmp(list->macros[i].name, trimmed_name) == 0)
        {
            result = list->macros[i].code;
            printf("result count: %d\n", list->macros[i].codeCount);
            break;
        }
    }
    return result;
}

int onFinish(MacroList *list)
{
    int i, j;
    if (list == NULL)
    {
        return 1;
    }

    for (i = 0; i < list->count; i++)
    {
        free(list->macros[i].name);

        for (j = 0; j < list->macros[i].codeCount; j++)
        {
            free(list->macros[i].code[j]);
        }

        free(list->macros[i].code);
    }
    free(list->macros);
    free(list);
    return 0;
}
