#include "main.h"

/**
 * get_location - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *get_location(char *command)
{
	char *path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	dirs = get_path_dir(path + 5);
	head = dirs;
	while (dirs)
	{
		temp = malloc(strlen(dirs->dir) + 1 + strlen(command) + 1);
		if (!temp)
			return (NULL);
		strcpy(temp, dirs->dir);
		strcat(temp, "/");
		strcat(temp, command);
		if (stat(temp, &st) == 0)
		{
			free_list(head);
			free(command);
			return (temp);
		}
		dirs = dirs->next;
		free(temp);
	}
	free(command);
	free_list(head);
	return (NULL);
}