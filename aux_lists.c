#include "main.h"

/**
 * add_separator_node_end - Add a separator found at the end of a sep_list.
 *
 * @head: Head of the linked list.
 * @separator: Separator found (; | &).
 *
 * Return: Address of the head.
 */
sep_list *add_separator_node_end(sep_list **head, char separator)
{
	sep_list *new_node, *temp_node;

	new_node = malloc(sizeof(sep_list));
	if (new_node == NULL)
		return (NULL);

	new_node->separator = separator;
	new_node->next = NULL;
	temp_node = *head;

	if (temp_node == NULL)
	{
		*head = new_node;
	}
	else
	{
		while (temp_node->next != NULL)
			temp_node = temp_node->next;
		temp_node->next = new_node;
	}

	return (*head);
}

/**
 * free_separator_list - Free a sep_list.
 *
 * @head: Head of the linked list.
 *
 * Return: No return value.
 */
void free_separator_list(sep_list **head)
{
	sep_list *temp_node;
	sep_list *current_node;

	if (head != NULL)
	{
		current_node = *head;
		while ((temp_node = current_node) != NULL)
		{
			current_node = current_node->next;
			free(temp_node);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - Add a command line at the end of a line_list.
 *
 * @head: Head of the linked list.
 * @line: Command line.
 *
 * Return: Address of the head.
 */
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new_node, *temp_node;

	new_node = malloc(sizeof(line_list));
	if (new_node == NULL)
		return (NULL);

	new_node->line = line;
	new_node->next = NULL;
	temp_node = *head;

	if (temp_node == NULL)
	{
		*head = new_node;
	}
	else
	{
		while (temp_node->next != NULL)
			temp_node = temp_node->next;
		temp_node->next = new_node;
	}

	return (*head);
}

/**
 * free_line_list - Free a line_list.
 *
 * @head: Head of the linked list.
 *
 * Return: No return value.
 */
void free_line_list(line_list **head)
{
	line_list *temp_node;
	line_list *current_node;

	if (head != NULL)
	{
		current_node = *head;
		while ((temp_node = current_node) != NULL)
		{
			current_node = current_node->next;
			free(temp_node);
		}
		*head = NULL;
	}
}

