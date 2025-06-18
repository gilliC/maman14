#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macroDefintions.h"

MacroList *createMacroList()
{
    MacroList *list = malloc(sizeof(MacroList));
    list->macros = NULL;
    list->count = 0;
    return list;
}

void createNewMacro(MacroList *list, const char *name)
{
    list->macros = realloc(list->macros, (list->count + 1) * sizeof(Macro));
    list->macros[list->count].name = malloc(strlen(name) + 1);
    strcpy(list->macros[list->count].name, name);
    list->macros[list->count].code = NULL;
    list->macros[list->count].codeCount = 0;
    list->count++;
}

void addCodeLine(MacroList *list, const char *name, const char *code)
{
    for (int i = 0; i < list->count; i++)
    {
        if (strcmp(list->macros[i].name, name) == 0)
        {
            list->macros[i].code = realloc(list->macros[i].code, (list->macros[i].codeCount + 1) * sizeof(char *));
            list->macros[i].code[list->macros[i].codeCount] = malloc(strlen(code) + 1);
            strcpy(list->macros[i].code[list->macros[i].codeCount], code);
            list->macros[i].codeCount++;
            return;
        }
    }
}

char **getCodeByName(MacroList *list, const char *name, int *count)
{
    for (int i = 0; i < list->count; i++)
    {
        if (strcmp(list->macros[i].name, name) == 0)
        {
            *count = list->macros[i].codeCount;
            return list->macros[i].code;
        }
    }
    *count = 0;
    return NULL;
}

void freeMacroList(MacroList *list)
{
    for (int i = 0; i < list->count; i++)
    {
        free(list->macros[i].name);
        for (int j = 0; j < list->macros[i].codeCount; j++)
        {
            free(list->macros[i].code[j]);
        }
        free(list->macros[i].code);
    }
    free(list->macros);
    free(list);
}
