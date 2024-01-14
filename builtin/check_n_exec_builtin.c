#include "../minishell.h"

int check_n_exec_builtin(t_cmd *cmd_info, t_exec *exec_info)
{
	char	*cmd;

	cmd = cmd_info->cmd_args[0];
	if (ft_strncmp(cmd, "echo", 4) == TRUE)
	{
		g_exit_code = echo(cmd_info->cmd_args);
	}
	else if (ft_strncmp(cmd, "cd", 2) == TRUE)
	{
		g_exit_code = cd(cmd_info->cmd_args, exec_info);
	}
	else if (ft_strncmp(cmd, "pwd", 3) == TRUE)
	{
		g_exit_code = pwd();
	}
	else if (ft_strncmp(cmd, "export", 6) == TRUE)
	{
		g_exit_code = export(exec_info, cmd_info->cmd_args);
	}
	else if (ft_strncmp(cmd, "unset", 5) == TRUE)
	{
		g_exit_code = unset(exec_info, cmd_info->cmd_args);
	}
	else if (ft_strncmp(cmd, "env", 3) == TRUE)
	{
		g_exit_code = env(exec_info);
	}
	else if (ft_strncmp(cmd, "exit", 4) == TRUE)
	{
		g_exit_code = exit_shell();
	}
	else
		return (FALSE);
	return (TRUE);
}