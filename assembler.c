#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i;

    /* Check if at least one filename is provided */
    if (argc < 2)
    {
        fprintf(stderr, "Error: At least one filename must be provided\n");
        fprintf(stderr, "Usage: %s <filename1> [filename2] ...\n", argv[0]);
        return 1;
    }

    /* Process each filename */
    for (i = 1; i < argc; i++)
    {
        if (access(argv[i], F_OK) == 0)
        {
            printf("File '%s': SUCCESS - file exists\n", argv[i]);
        }
        else
        {
            printf("File '%s': FAILURE - file does not exist\n", argv[i]);
        }
    }

    return 0;
}
