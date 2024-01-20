#include "../minishell.h"

int exit_shell(int exit_flag)
{
	if (exit_flag == TRUE)
		exit_flag = FALSE;
	printf("exit\n");
	exit(SUCCESS);
}
