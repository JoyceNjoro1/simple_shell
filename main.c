#include "main.h"
<<<<<<< HEAD
#include "string.h"

/**
 * cd_shell - Change the current directory based on input.
 * @datash: A pointer to data relevant to the shell.
 *
 * Return: 1 on success.
 */
int cd_shell(data_shell *datash)
{
    char *target_dir;
    int is_home, is_home2, is_ddash;

    target_dir = datash->args[1];

    if (target_dir != NULL)
    {
        is_home = strcmp("$HOME", target_dir);
        is_home2 = strcmp("~", target_dir);
        is_ddash = strcmp("--", target_dir);
    }

    if (target_dir == NULL || is_home == 0 || is_home2 == 0 || is_ddash == 0)
    {
        cd_to_home(datash);
        return (1);
    }

    if (strcmp("-", target_dir) == 0)
    {
        cd_previous(datash);
        return (1);
    }

    if (strcmp(".", target_dir) == 0 || strcmp("..", target_dir) == 0)
    {
    }

    return (1);
}

=======
/**
 * free_data - frees data struc
 *
 * @datash: data struc
 * Return: no return
 */
void free_data(data_shell *datash)
{
	unsigned int i;

	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - Ini data struc
 *
 * @datash: data struc
 * @av: argument vector
 * Return: no return
 */
void set_data(data_shell *datash, char **av)
{
	unsigned int i;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	datash->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = _strdup(environ[i]);
	}

	datash->_environ[i] = NULL;
	datash->pid = aux_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datash, av);
	shell_loop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
>>>>>>> 787ddf254a2b1a95661a5d2db2bdd0627a04ef32
