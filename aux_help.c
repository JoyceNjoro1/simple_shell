#include "main.h"

/**
 * help_env - Display help information for the 'env' builtin.
 */
void help_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Print the environment of the shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_setenv - Display help information for the 'setenv' builtin.
 */
void help_setenv(void)
{
	char *help = "setenv: setenv [name] [value] [replace]\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Add or update an environment variable.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_unsetenv - Display help information for the 'unsetenv' builtin.
 */
void help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv [name]\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Remove an environment variable.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_general - Display general help information for the shell.
 */
void help_general(void)
{
	char *help = "^-^ shell, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "These commands are defined internally. Type 'help' to see the list.";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Type 'help [command]' to find out more about a specific command.\n\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "[dir]\nexit: exit [status]\n env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "[args]]\n setenv: setenv [variable] [value] [replace]\n";
	write(STDOUT_FILENO, help, _strlen(help));
	help = " unsetenv: unsetenv [variable]\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_exit - Display help information for the 'exit' builtin.
 */
void help_exit(void)
{
	char *help = "exit: exit [status]\n Exit the shell.\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Exits the shell with a status code [status]. If omitted, the exit";
	write(STDOUT_FILENO, help, _strlen(help));
	help = " status is that of the last executed command.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

