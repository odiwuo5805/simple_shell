#include "shell.h"


/**
 * _getenv - gets the value of the global variable
 * @name: name of the global variable
 * Return: string of value
 */
char *_getenv(const char *name)
{
	int k, j;
	char *value;

	if (!name)
		return (NULL);
	for (k = 0; environ[k]; k++)
	{
		j = 0;
		if (name[j] == environ[k][j])
		{
			while (name[j])
			{
				if (name[j] != environ[k][j])
					break;

				j++;
			}
			if (name[j] == '\0')
			{
				value = (environ[k] + j + 1);
				return (value);
			}
		}
	}
	return (0);
}


/**
 * add_node_end - adds a new node at the end of a list_t list
 * @head: pointer to pointer to our linked list
 * @str: pointer to string in previous first node
 * Return: address of the new element/node
 */

list_path *add_node_end(list_path **head, char *str)
{

	list_path *tmp;
	list_path *new;

	new = malloc(sizeof(list_path));

	if (!new || !str)
	{
		return (NULL);
	}

	new->dir = str;

	new->p = '\0';
	if (!*head)
	{
		*head = new;
	}
	else
	{
		tmp = *head;

		while (tmp->p)
		{

			tmp = tmp->p;
		}

		tmp->p = new;
	}

	return (*head);
}


/**
 * linkpath - creates a linked list for path directories
 * @path: string of path value
 * Return: pointer to the created linked list
 */
list_path *linkpath(char *path)
{
	list_path *head = '\0';
	char *token;
	char *cpath = _strdup(path);

	token = strtok(cpath, ":");
	while (token)
	{
		head = add_node_end(&head, token);
		token = strtok(NULL, ":");
	}

	return (head);
}

/**
 * _which - finds the pathname of a filename
 * @filename: name of file or command
 * @head: head of linked list of path directories
 * Return: pathname of filename or NULL if no match
 */
char *_which(char *filename, list_path *head)
{
	struct stat st;
	char *strin;

	list_path *tmp = head;

	while (tmp)
	{

		strin = concat_all(tmp->dir, "/", filename);
		if (stat(strin, &st) == 0)
		{
			return (strin);
		}
		free(strin);
		tmp = tmp->p;
	}

	return (NULL);
}

/**
 * free_list - frees a list_t
 *@head: pointer to our linked list
 */
void free_list(list_path *head)
{
	list_path *storage;

	while (head)
	{
		storage = head->p;
		free(head->dir);
		free(head);
		head = storage;
	}

}
