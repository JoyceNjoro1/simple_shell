#include "main.h"

/**
 * add_runtime_variable - Add a variable at the end of a runtime variable list.
 *
 * @head: Head of the linked list.
 * @var_length: Length of the variable.
 * @value: Value of the variable.
 * @value_length: Length of the value.
 *
 * Return: Address of the head.
 */
r_var *add_runtime_variable(r_var **head, int var_length, char *value, int value_length)
{
	r_var *new_node, *temp_node;

	new_node = malloc(sizeof(r_var));
	if (new_node == NULL)
		return (NULL);

	new_node->len_var = var_length;
	new_node->val = value;
	new_node->len_val = value_length;

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
 * free_runtime_variable_list - Free a runtime variable list.
 *
 * @head: Head of the linked list.
 *
 * Return: No return value.
 */
void free_runtime_variable_list(r_var **head)
{
	r_var *temp_node;
	r_var *current_node;

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

