#include "main.h"

/**
 * handle_exit - Vérifie si la commande est "exit"
 * @args: Tableau d'arguments
 * Return: 1 si c'est "exit", 0 sinon
 */
int handle_exit(char **args)
{
	if (args[0] != NULL && strcmp(args[0], "exit") == 0)
		return (1);
	return (0);
}

/**
 * handle_env - Affiche les variables d'environnement
 * Return: Aucun, car la fonction retourne void.
 */
void handle_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * main - Point d'entrée du programme shell.
 * @ac: Nombre d'arguments.
 * @av: Tableau des arguments passés au programme.
 * Return: Toujours 0 (Succès).
 */
int main(int ac, char **av)
{
	char *line = NULL;  /* Stocke la ligne d'entrée de l'utilisateur */
	size_t len = 0;
	ssize_t read;
	/*ssize_t read;*/
	char **args;        /* Stocke les tokens extraits de la ligne d'entrée */
	(void)ac, (void)av; /* Paramètre inutilisé */

	while (1)
	{
		printf("$ ");

		read = getline(&line, &len, stdin);  /* Récupérer la ligne d'entrée */
		/*handle_read_error(line, read);*/

		if (read == -1) {
			free(line);
			perror("getline");
			exit(0);
		}
		cleaner(line);


		args = split_line(line);
        if (!args)
        {
            cleanup(line, NULL);
            line = NULL;
            continue;
        }

        if (handle_exit(args))
        {
            cleanup(line, args);
            exit(0);
        }
        else if (strcmp(args[0], "env") == 0)
        {
            handle_env();
            cleanup(line, args);
            line = NULL;
        }
        else
        {
            execute_command(args, av);
            cleanup(line, args);
            line = NULL;
        }
    }
    return (0);
}
