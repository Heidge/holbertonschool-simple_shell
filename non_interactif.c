#include "main.h"

/**
 * handle_non_interactive - Gère le shell en mode non interactif
 * @av: Tableau contenant argv[0]
 */
void handle_non_interactive(char **av)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **args = NULL;
    char *simple_args[2] = {NULL, NULL};

    while ((read = getline(&line, &len, stdin)) != -1)
    {
        cleaner(line);
        if (line[0] == '\0')
            continue;

        if (strchr(line, ' ') == NULL)
        {
            simple_args[0] = line;
            simple_args[1] = NULL;
            execute_command(simple_args, av);
            free(line);
            exit(0);
        }
        else
        {
            args = split_line(line);
            if (!args || !args[0])
            {
                cleanup(line, args);
                continue;
            }

            if (strcmp(args[0], "exit") == 0)
            {
                cleanup(line, args);
                exit(0);
            }

            execute_command(args, av);
            cleanup(line, args);
            exit(0);
        }
    }
    free(line);
}
