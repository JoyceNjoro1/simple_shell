#include "main.h"

/**
 * printEnvHelp - Print help information for the built-in env command
 * Return: no return
 */
void printEnvHelp(void)
{
    char *helpText = "env: env [option] [name=value] [command [args]]\n\t";

    write(STDOUT_FILENO, helpText, _strlen(helpText));
    helpText = "Display the environment of the shell.\n";
    write(STDOUT_FILENO, helpText, _strlen(helpText));
}

/**
 * printSetenvHelp - Print help information for the built-in setenv command
 * Return: no return
 */
void printSetenvHelp(void)
{
    char *helpText = "setenv: setenv (const char *name, const char *value, int replace)\n\t";

    write(STDOUT_FILENO, helpText, _strlen(helpText));
    helpText = "Add a new definition to the environment\n";
    write(STDOUT_FILENO, helpText, _strlen(helpText));
}

/**
 * printUnsetenvHelp - Print help information for the built-in unsetenv command
 * Return: no return
 */
void printUnsetenvHelp(void)
{
    char *helpText = "unsetenv: unsetenv (const char *name)\n\t";

    write(STDOUT_FILENO, helpText, _strlen(helpText));
    helpText = "Remove an entry completely from the environment\n";
    write(STDOUT_FILENO, helpText, _strlen(helpText));
}

/**
 * printGeneralHelp - Entry point for help information for the help built-in
 * Return: no return
 */
void printGeneralHelp(void)
{
    char *helpText = "^-^ MyShell, version 1.0(1)-release\n";

    write(STDOUT_FILENO, helpText, _strlen(helpText));
    helpText = "These commands are defined internally. Type 'help' to see the list";
    write(STDOUT_FILENO, helpText, _strlen(helpText));
    helpText = "Type 'help name' to find out more about the function 'name'.\n\n ";
    write(STDOUT_FILENO, helpText, _strlen(helpText));
    helpText = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
    write(STDOUT_FILENO, helpText, _strlen(helpText));
    helpText = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
    write(STDOUT_FILENO, helpText, _strlen(helpText));
    helpText = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
    write(STDOUT_FILENO, helpText, _strlen(helpText));
    helpText = "unsetenv [variable]\n";
    write(STDOUT_FILENO, helpText, _strlen(helpText));
}

/**
 * printExitHelp - Print help information for the built-in exit command
 * Return: no return
 */
void printExitHelp(void)
{
    char *helpText = "exit: exit [n]\n Exit the shell.\n";

    write(STDOUT_FILENO, helpText, _strlen(helpText));
    helpText = "Exits the shell with a status of N. If N is omitted, the exit";
    write(STDOUT_FILENO, helpText, _strlen(helpText));
    helpText = "status is that of the last command executed.\n";
    write(STDOUT_FILENO, helpText, _strlen(helpText));
}

