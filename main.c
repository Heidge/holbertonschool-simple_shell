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
 * handle_read_error - Gère les erreurs de la fonction read, dont EOF (Ctrl+D)
 * @line: ligne à libérer en cas d'erreur
 * @read: valeur de retour de la fonction getline
 * Libère la mémoire, détecte si EOF est atteint (errno == 0) ou erreur
 */
void handle_read_error(char *line, ssize_t read)
{
	if (read == -1)
	{
		free(line);
		printf("C'est moi qui merde ! %d", errno);
		if (errno == 0)
		{
			/* EOF (Ctrl+D) sans erreur → on quitte normalement */
			exit(0);
		}
		else
		{
			/* Autre erreur → message d'erreur + sortie */
			perror(": command not found.");
			exit(1);
		}
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
	errno = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))/*si prog interactif, affiche l'invite*/
			printf("$ ");
		else
			handle_non_interactive(av);

		read = getline(&line, &len, stdin);  /* Récupérer la ligne d'entrée */
		/*handle_read_error(line, read);*/

		if (read == -1) {
			free(line);
			if (feof(stdin)) {
				exit(0);
			}
			perror("getline");
			exit(1);
		}
		cleaner(line);


		args = split_line(line);  /* Découper la ligne en tokens */
		if (!args)
		{
			free(line);
			continue;
		}

		if (handle_exit(args))/* Gérer les commandes comme exit et env */
		{
			free(line);
			free(args);
			exit(0);
		}
		else if (strcmp(args[0], "env") == 0)
			handle_env();
		else
			execute_command(args, av); /* Exécuter les autres cmd */
	}
	return (0);
}
