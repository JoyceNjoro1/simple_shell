#include "main.h"

/**
 * handle_sigint - Handle the Ctrl+C signal in the prompt.
 *
 * @sig: Signal received.
 */
void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}

