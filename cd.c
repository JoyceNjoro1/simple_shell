#include "main.h"

/**
 * cd_dot - Change to the parent dir
 *
 * @datash: Data structure containing relevant inf
 */
void cd_dot(data_shell *datash)
{
    char current_path[PATH_MAX];
    char *dir, *copy_pwd, *tokenized_pwd;

    getcwd(current_path, sizeof(current_path));
    copy_pwd = _strdup(current_path);
    set_env("OLDPWD", copy_pwd, datash);
    dir = datash->args[1];

    if (_strcmp(".", dir) == 0)
    {
        set_env("PWD", copy_pwd, datash);
        free(copy_pwd);
        return;
    }

    if (_strcmp("/", copy_pwd) == 0)
    {
        free(copy_pwd);
        return;
    }

    tokenized_pwd = copy_pwd;
    rev_string(tokenized_pwd);
    tokenized_pwd = _strtok(tokenized_pwd, "/");

    if (tokenized_pwd != NULL)
    {
        tokenized_pwd = _strtok(NULL, "\0");

        if (tokenized_pwd != NULL)
            rev_string(tokenized_pwd);
    }

    if (tokenized_pwd != NULL)
    {
        chdir(tokenized_pwd);
        set_env("PWD", tokenized_pwd, datash);
    }
    else
    {
        chdir("/");
        set_env("PWD", "/", datash);
    }

    datash->status = 0;
    free(copy_pwd);
}

/**
 * cd_to - Change to a dir speci by user
 *
 * @datash: Data structure containing relevant inf
 */
void cd_to(data_shell *datash)
{
    char current_path[PATH_MAX];
    char *dir, *copy_pwd, *copy_dir;

    getcwd(current_path, sizeof(current_path));
    dir = datash->args[1];

    if (chdir(dir) == -1)
    {
        get_error(datash, 2);
        return;
    }

    copy_pwd = _strdup(current_path);
    set_env("OLDPWD", copy_pwd, datash);
    copy_dir = _strdup(dir);
    set_env("PWD", copy_dir, datash);

    free(copy_pwd);
    free(copy_dir);

    datash->status = 0;

    chdir(dir);
}

/**
 * cd_previous - Change to the prev dir
 *
 * @datash: Data structure containing relevant in
 */
void cd_previous(data_shell *datash)
{
    char current_path[PATH_MAX];
    char *previous_pwd, *previous_oldpwd, *copy_pwd, *copy_oldpwd;

    getcwd(current_path, sizeof(current_path));
    copy_pwd = _strdup(current_path);
    previous_oldpwd = _getenv("OLDPWD", datash->_environ);

    if (previous_oldpwd == NULL)
        copy_oldpwd = copy_pwd;
    else
        copy_oldpwd = _strdup(previous_oldpwd);

    set_env("OLDPWD", copy_pwd, datash);

    if (chdir(copy_oldpwd) == -1)
        set_env("PWD", copy_pwd, datash);
    else
        set_env("PWD", copy_oldpwd, datash);

    previous_pwd = _getenv("PWD", datash->_environ);

    write(STDOUT_FILENO, previous_pwd, _strlen(previous_pwd));
    write(STDOUT_FILENO, "\n", 1);

    free(copy_pwd);
    if (previous_oldpwd)
        free(copy_oldpwd);

    datash->status = 0;

    chdir(previous_pwd);
}

/**
 * cd_to_home - Change to the home dir
 *
 * @datash: Data structure containing relevant inf
 */
void cd_to_home(data_shell *datash)
{
    char *previous_pwd, *home;
    char current_path[PATH_MAX];

    getcwd(current_path, sizeof(current_path));
    previous_pwd = _strdup(current_path);
    home = _getenv("HOME", datash->_environ);

    if (home == NULL)
    {
        set_env("OLDPWD", previous_pwd, datash);
        free(previous_pwd);
        return;
    }

    if (chdir(home) == -1)
    {
        get_error(datash, 2);
        free(previous_pwd);
        return;
    }

    set_env("OLDPWD", previous_pwd, datash);
    set_env("PWD", home, datash);
    free(previous_pwd);
    datash->status = 0;
}
