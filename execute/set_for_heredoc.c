/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_for_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:13:47 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 23:20:42 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	repalce_env_process(char **line, int i, int start_idx, char *value)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin_free(ft_substr(*line, 0, start_idx - 1), value);
	tmp2 = ft_strjoin_free(tmp, *line + i);
	free(*line);
	*line = tmp2;
}

void	replace_env_in_line(char **line, t_env *env)
{
	int		i;
	int		start_idx;
	char	*key;
	char	*value;

	i = 0;
	start_idx = 0;
	while (i < (int)ft_strlen(*line) && (*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] != '\0')
		{
			start_idx = ++i;
			key = find_key(*line, &i, &start_idx);
			value = find_value(env, key, NULL);
			free(key);
			if (value == NULL)
				continue ;
			repalce_env_process(line, i, start_idx, value);
			i = start_idx + ft_strlen(value) - 1;
		}
		i++;
	}
}

void	exec_heredoc(t_env *env, char *new_filename, char *limiter)
{
	int		fd;
	char	*line;

	fd = open(new_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == FAILURE)
	{
		perror("open failed\n");
		exit(EXIT_FAILURE);
	}
	while (TRUE)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		replace_env_in_line(&line, env);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

static void	replace_filename(t_cmd *node, t_shell *shell_info, int num)
{
	char	*n;
	char	*new_filename;
	t_redir	*tmp_redir;

	while (node != NULL)
	{
		tmp_redir = node->redir;
		while (tmp_redir != NULL)
		{
			if (tmp_redir->type == HEREDOC)
			{
				n = ft_itoa(num);
				new_filename = ft_strjoin("/tmp/hrd_", n);
				num++;
				exec_heredoc(shell_info->env, new_filename, \
				tmp_redir->filename);
				free(tmp_redir->filename);
				tmp_redir->filename = new_filename;
				free(n);
			}
			tmp_redir = tmp_redir->next;
		}
		node = node->next;
	}
}

int	set_for_heredoc(t_shell *shell_info)
{
	pid_t	pid;
	t_cmd	*node;
	int		status;

	set_signal(IGNORE, IGNORE);
	pid = fork();
	if (pid == FAILURE)
		exit(EXIT_FAILURE);
	else if (pid == SUCCESS)
	{
		set_signal(HRD_CHILD, HRD_CHILD);
		exit(EXIT_SUCCESS);
	}
	wait(&status);
	if (WEXITSTATUS(status) == EXIT_FAILURE)
		g_exit_code = EXIT_FAILURE;
	set_signal(MINIVELL, MINIVELL);
	node = shell_info->cmd;
	replace_filename(node, shell_info, 0);
	if (g_exit_code == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (SUCCESS);
}
