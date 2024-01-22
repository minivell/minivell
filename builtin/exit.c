#include "../minishell.h"

int exit_shell(char **cmd_args, int exit_flag)
{
	if (exit_flag == FALSE)
		printf("exit\n");
	if (cmd_args[1] == NULL)
		exit(EXIT_SUCCESS);
	if (cmd_args[2] != NULL)
	{
		print_error_message(cmd_args[0], NULL, "too many arguments");
		return (EXIT_FAILURE);
	}
	if (check_num(cmd_args[1]) == FALSE)
	{
		print_error_message(cmd_args[0], cmd_args[1], "numeric argument required");
		exit(255);
	}
	if (exit_flag == TRUE)
		exit(ft_atoi(cmd_args[1]) % 256);
	else
		exit(ft_atoi(cmd_args[1]));
}
