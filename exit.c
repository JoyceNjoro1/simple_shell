#include "main.h"

/**
 * exit_shell - function to exit the shell
 *
 * @datash: arguments to the exit function
 * Return: 0 on success.
 */
int exit_shell(data_shell *datash)
{
	unsigned int istatus;
	int is_digitt;
	int str_leng;
	int big_number;

	if (datash->args[1] != NULL)
	{
		istatus = _atoi(datash->args[1]);
		is_digitt = _isdigit(datash->args[1]);
		str_leng = _strlen(datash->args[1]);
		big_number = istatus > (unsigned int)INT_MAX;
		if (!is_digitt || str_leng > 10 || big_number)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (istatus % 256);
	}
	return (0);
}
