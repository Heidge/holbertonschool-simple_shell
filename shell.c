#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/*protos*/
void display_prompt(void);
void execute_command(char *line, char **argv);
char *trim_whitespace(char *str);
int is_whitespace(char c);

/**
* main - boucle principale et affichage du prompt
* @argc: compteur d'argument (non utilisé ici)
* @argv: vecteur d'argument (contien nom du programme ou arguments
* Return: 0
*/

int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int interactive;
	char *trimmed_line;

	(void)argc; /*argc n'est pas utilisé donc on le mute*/

	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			display_prompt();

		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			if (interactive)
				printf("\n");
			break;
		}

		line[nread - 1] = '\0'; /*supprime le \n en fin de commande*/

		trimmed_line = trim_whitespace(line);

		if (trimmed_line[0] != '\0') /* Ignore les lignes vides */
		{
			if (strcmp(trimmed_line, "exit") == 0)
			{
				free(trimmed_line);
				break;
			}

			execute_command(trimmed_line, argv);
			free(trimmed_line);
		}
	}

	free(line);
	return (0);
}

/**
* display_prompt - affiche le shell prompt
*/

void display_prompt(void)
{
	printf("($)");
	fflush(stdout);
}

/**
* is_whitespace - vérifie si un caractère est un espace blanc
* @c: caractère à vérifier
* Return: 1 si c'est un espace blanc, 0 sinon
*/
int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

/**
* trim_whitespace - supprime les espaces en début et fin de chaîne
* @str: chaîne à nettoyer
* Return: nouvelle chaîne allouée sans espaces superflus
*/
char *trim_whitespace(char *str)
{
	char *end;
	char *start;
	char *new_str;
	size_t len;

	if (str == NULL)
		return NULL;

	/* Trouve le premier caractère non-espace */
	start = str;
	while (*start && is_whitespace(*start))
		start++;

	if (*start == '\0') /* Chaîne vide ou que des espaces */
	{
		new_str = malloc(1);
		if (new_str)
			new_str[0] = '\0';
		return new_str;
	}

	/* Trouve le dernier caractère non-espace */
	end = start + strlen(start) - 1;
	while (end > start && is_whitespace(*end))
		end--;

	/* Calcule la longueur et alloue une nouvelle chaîne */
	len = end - start + 1;
	new_str = malloc(len + 1);

	if (new_str == NULL)
		return NULL;

	/* Copie la partie utile */
	strncpy(new_str, start, len);
	new_str[len] = '\0';

	return new_str;
}

/**
* execute_command - crée les forks et execute les commandes
* @line: entrée utilisateur
* @argv: vecteur d'argument de la fonction main
*/

void execute_command(char *line, char **argv)
{
	pid_t pid;
	int status;
	char *cmd_argv[2];

	if (line[0] == '\0')
		return;

	pid = fork();

	if (pid == -1)
	{
		perror("erreur fork");
		return;
	}

	if (pid == 0)
	{
		if (access(line, X_OK) == -1)
		{
			fprintf(stderr, "%s: No such file or directory\n", argv[0]);
			exit(EXIT_FAILURE);
		}

		cmd_argv[0] = line;
		cmd_argv[1] = NULL;

		if (execve(line, cmd_argv, environ) == -1)
		{
			fprintf(stderr, "%s: No such file or directory\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);
}
