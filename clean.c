#include "main.h"

/**
 * cleanup - Libère la mémoire allouée pour la ligne et les arguments
 * @line: Ligne lue
 * @args: Arguments de la commande
 */
void cleanup(char *line, char **args)
{
	free(line); /*libération de la mémoire de line*/
	free(args); /*libération de la mémoire de l'array de mots*/
}

/**
 * cleaner - nettoyage du \n
 *
 * @line: string
 */

void cleaner(char *line)
{
	int i;

	if (line == NULL)/*Vérifie que line n'est pas NULL*/
	{
		return;/*Si line est NULL, on ne fait rien*/
	}

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			return;
		}
	}
}
