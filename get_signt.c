#include "main.h"

/**
 * get_sigint - Handle the crtl + c
 * @sig: Sign handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
