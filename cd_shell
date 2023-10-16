#include "main.h"

/**
 * custom_cd_shell - Change the current directory based on input.
 * @datash: A pointer to data relevant to the shell.
 *
 * Return: 1 on success.
 */
int custom_cd_shell(data_shell *datash)
{
    char *dir;
    int ishome, ishome2, isddash;

    dir = datash->args[1];

    if (dir != NULL)
 {
        ishome = _strcmp("$HOME", dir);
        ishome2 = _strcmp("~", dir);
        isddash = _strcmp("--", dir);
    }

    if (dir == NULL || !ishome || !ishome2 || !isddash)
    {
        custom_cd_to_home(datash);
        return 1;
    }

    if (_strcmp("-", dir) == 0)
    {
   custom_cd_previous(datash);
        return 1;
    }

    if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
    {
        custom_cd_dot(datash);
        return 1;
    }

    custom_cd_to(datash);

    return 1;
}

