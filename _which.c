#include "main.h"

/**
 * find_command_in_path - Cherche une commande dans les répertoires du PATH
 * @cmd: Nom de la commande à chercher
 *
 *Cette fonction parcourt les différents répertoires listés dans la variable
 * d'environnement PATH. Pour chaque répertoire, elle concatène le chemin
 * avec la commande donnée, puis vérifie si ce fichier existe à l'aide de
 * la fonction stat(). Si un chemin valide est trouvé, la fonction retourne
 * une chaîne de caractères contenant le chemin complet de la commande.
 * Si aucun chemin valide n'est trouvé, ou en cas d'erreur mémoire, elle
 * retourne NULL.
 *
 * Return: Chaîne contenant le chemin absolu de la cmd, ou NULL si non trouvé
 */
char *find_command_in_path(const char *cmd)
{
	char *path = getenv("PATH"); /*on récupère le PATH en entier*/
	/*array(s) pour récup les mots de la cmd, une copie du path et un array*/
	char *token, *path_copy, *full_path;
	/*structure pour stocker les informations de stat()*/
	struct stat st;
	size_t len; /*nb de caractères des buffers token et path_copy*/

	if (!path || !cmd) /*si le path ou la commande vaut NULL*/
		return (NULL); /*on retourne NULL*/

	path_copy = strdup(path); /*copie du path,pas de modif dans path d'origine*/
	token = strtok(path_copy, ":"); /*on dit quoi découper(path_copy) et où(:)*/

	while (token != NULL) /*on boucle dans le buffer de path découpé*/
	{
/*on calcule le nb de caractère de token & cmd + le caractère "/" et de fin*/
		len = strlen(token) + strlen(cmd) + 2;
		full_path = malloc(len); /*on alloue la mémoire du nouveau buffer*/
		if (full_path == NULL) /*si l'allocation échoue*/
		{
			free(path_copy); /*on libère la mémoire de path_copy*/
			return (NULL); /*et on retourne NULL*/
		}
/*dans full_path on print un certain nb de char (len) dans le format "%s/%s"*/
/*avec les strings token et cmd*/
		snprintf(full_path, len, "%s/%s", token, cmd);

		/*on vérifie si la commande est trouvée dans le PATH*/
		if (stat(full_path, &st) == 0)
		{
			free(path_copy); /*on libére la mémoire de path_copy car plus besoin*/
			return (full_path); /*on retourne le path de la commande*/
		}

		free(full_path);/*on libère la mémoire pour pouvoir traiter une autre cmd*/
		token = strtok(NULL, ":");/*on découpe le path (voilà pq copie du path)*/
	}

	free(path_copy); /*on peu libérer la mémoire de path_copy car plus besoin*/
	return (NULL); /*on renvoie NULL par ce que cmd pas trouvée dans le path*/
}
