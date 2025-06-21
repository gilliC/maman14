#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macroDefintions.h"

MacroList *createMacroList(void)
{
    MacroList *list = malloc(sizeof(MacroList));
    list->macros = NULL;
    list->count = 0;
    return list;
}

int createNewMacro(MacroList *list, const char *name)
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

int addCodeLine(MacroList *list, const char *name, const char *code)
{
    printf("addCodeLine: %s %s\n", name, code);
    char **temp;
    int i;
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

            list->macros[i].code[list->macros[i].codeCount] = malloc(strlen(code) + 1);
            if (list->macros[i].code[list->macros[i].codeCount] == NULL)
            {
                fprintf(stderr, "Memory allocation failed for code line in macro '%s'\n", name);
                return 1;
            }
            strcpy(list->macros[i].code[list->macros[i].codeCount], code);
            list->macros[i].codeCount++;
            printf("addCodeLine: %s %s\n", name, code);
            printf("list->macros[i].codeCount: %d\n", list->macros[i].codeCount);

            return 0;
        }
    }
    fprintf(stderr, "Macro '%s' not found\n", name);
    return 1;
}

char **getCodeByName(MacroList *list, const char *name)
{
    int i;
    for (i = 0; i < list->count; i++)
    {
        if (strcmp(list->macros[i].name, name) == 0)
        {
            return list->macros[i].code;
        }
    }
    return NULL;
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
