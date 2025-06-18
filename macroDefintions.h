typedef struct
{
    char *name;
    char **code;
    int codeCount;
} Macro;

typedef struct
{
    Macro *macros;
    int count;
} MacroList;

MacroList *createMacroList();
void createNewMacro(MacroList *list, const char *name);
void addCodeLine(MacroList *list, const char *name, const char *code);
char **getCodeByName(MacroList *list, const char *name, int *count);
void freeMacroList(MacroList *list);
