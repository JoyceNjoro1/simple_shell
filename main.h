#ifndef  _SHELL_H_
#define _SHELL_H_

#include "main.h"
#include "include/data_shell.h"

int cd_shell(data_shell *datash);
void cd_to_home(data_shell *datash);
void cd_previous(data_shell *datash);
void cd_dot(data_shell *datash);
void cd_to(data_shell *datash);

#endif
