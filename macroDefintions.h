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
int createNewMacro(MacroList *list, const char *name);
int addCodeLine(MacroList *list, const char *name, const char *code);
char **getCodeByName(MacroList *list, const char *name);
int onFinish(MacroList *list);
