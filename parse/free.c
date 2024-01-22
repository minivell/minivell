#include "../minishell.h"

void	free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir != NULL)
	{
		tmp = redir->next;
		free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

void	free_str_arr(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_str_arr_line(char **arr, int len)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (i < len)
		free(arr[i++]);
	free(arr);
}
