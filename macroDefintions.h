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

MacroList *createMacroList(void);
int createNewMacro(MacroList *list, char *name);
int addCodeLine(MacroList *list, char *name, char *code);
char **getCodeByName(MacroList *list, char *name, int *codeCount);
int onFinish(MacroList *list);
