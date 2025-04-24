#include "main.h"

/**
 * get_line - affiche un prompt "$ ", attend une commande
 * de l'utilisateur, puis l'affiche.
 * Il s'arrête proprement à la fin de fichier (Ctrl+D).
 *
 * Return: Always 0 (Success)
 */
char *get_line(void)
{
	/*pointeur vers chaine contenant la ligne de l'utilisateur*/
	char *line = NULL;
	/*taille initiale du buffer, getline ajuste la taille automatiquement*/
	size_t len = 0;
	/*stock le nombre de caractère lu par getline*/
	ssize_t read;

	errno = 0;/*initialise errno à zéro pour éviter d'anciennes valeurs*/

	read = getline(&line, &len, stdin);

	if (read == -1)
	{
		free(line);

		/*L'utilisateur tape EOF. Fin de fichier détectée. Le programme se fini*/
		if (errno == 0)/*variable globale qui contient code erreur d'une fonc*/
		{/*0 = pas d'erreur*/
			exit(0);
		}
		else/*Erreur de lecture*/
		{
			perror(": command not found.");
			exit(1);
		}
	}
	cleaner(line);/*appel fonction: nettoyage du \n et si line non valide*/

	return (line);
}
