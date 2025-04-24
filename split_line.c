#include "main.h"

/**
 * split_line - découpe une ligne en mots
 * @line: la ligne à découper
 *
 * Return: un tableau de mots (tokens)
 */

char **split_line(char *line)
{
	char **array_of_tokens; /*tableau de mots*/
	char *token; /*un mot*/
	int i = 0; /*variable de boucle pas l'index*/

	if (line == NULL)
		return (NULL);

	/*on alloue la mémoire : 64 = place max*/
	array_of_tokens = malloc(sizeof(char *) * 64);
	if (array_of_tokens == NULL) /*si l'allocation échoue*/
		return (NULL); /*renvoie NULL*/

	token = strtok(line, " "); /*on amorce la découpe avec strtok*/

	while (token != NULL) /*on boucle tant qu'il y a encore à découper*/
	{
		/*on envoie les mots (token) dans le tableau à mot (array_of_tokens)*/
		array_of_tokens[i] = token;
		i++; /*on avance dans le tableau de mot*/
		token = strtok(NULL, " "); /*on coupe dès qu'on trouve le séparateur*/
	}

	array_of_tokens[i] = NULL; /*on add un caractère null a la fin du array*/
	return (array_of_tokens); /*on renvoie le tableau de token*/
}
