#include "macroDefintions.h"

int transformMacros(char *filename, char errors[100][100]);
int isMacroEnd(char *line);
int isMacroDefinition(char *line, char *macro_name);
int isValidMacroName(char *name);

#define FILE_NAME_LENGTH 256
#define LINE_LENGTH 80
#define MACRO_NAME_DEFINITION_LENGTH 5 /* mcro and whitespace */
