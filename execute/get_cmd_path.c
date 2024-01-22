#include "../minishell.h"

char	*get_cmd_path(char *cmd, char **path)
{
	int		i;
	char	*cmd_path;
	char	*cmd_tmp;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (cmd == NULL || path == NULL)
		return (NULL);
	i = 0;
	cmd_tmp = ft_strjoin("/", cmd);
	if (cmd_tmp == NULL)
		exit (EXIT_FAILURE);
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmd_tmp);
		if (cmd_path == NULL)
			exit (EXIT_FAILURE);
		if (access(cmd_path, X_OK) == SUCCESS)
		{
			free(cmd_tmp);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	return (NULL);
}