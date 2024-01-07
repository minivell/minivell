#include "../minishell.h"

int check_n_exec_builtin(t_cmd *cmd_info)
{
	char	*cmd;

	cmd = cmd_info->cmd_args[0];
	if (ft_strncmp(cmd, "echo", 4) == TRUE)
	{
//		echo();
		return 0;
	}
	else if (ft_strncmp(cmd, "cd", 2) == TRUE)
	{
//		cd();
		return 0;
	}
	else if (ft_strncmp(cmd, "pwd", 3) == TRUE)
	{
//		pwd();
		return 0;
	}
	else if (ft_strncmp(cmd, "export", 6) == TRUE)
	{
//		export();
		return 0;
	}
	else if (ft_strncmp(cmd, "unset", 5) == TRUE)
	{
//		unset();
		return 0;
	}
	else if (ft_strncmp(cmd, "env", 3) == TRUE)
	{
//		env();
		return 0;
	}
	else if (ft_strncmp(cmd, "exit", 4) == TRUE)
	{
//		exit();
		return 0;
	}
	else
		return (FAILURE);
	return (SUCCESS);
}