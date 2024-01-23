/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:46:01 by gykoh             #+#    #+#             */
/*   Updated: 2024/01/23 13:46:02 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	alloc_word(t_token **tokens, t_cmd **new_cmd)
{
	int	cnt;

	cnt = 0;
	while (*tokens != NULL && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == WORD)
			cnt++;
		*tokens = (*tokens)->next;
	}
	*new_cmd = ft_calloc(1, sizeof(t_cmd));
	(*new_cmd)->cmd_args = ft_calloc(cnt + 1, sizeof(char *));
	(*new_cmd)->cmd_cnt = cnt;
}

void	handle_redir(t_token **cmd_tmp, t_token **tokens, \
	t_cmd **new_cmd, t_redir **new)
{
	int		i;
	char	*filename;

	i = 0;
	while (*cmd_tmp != *tokens)
	{
		if ((*cmd_tmp)->type >= OUT_REDIR && (*cmd_tmp)->type <= HEREDOC)
		{
			filename = ft_strdup((*cmd_tmp)->next->value);
			*new = new_redir((*cmd_tmp)->type, filename);
			add_back_redir(&((*new_cmd)->redir), (*new));
			*cmd_tmp = (*cmd_tmp)->next;
		}
		else
			(*new_cmd)->cmd_args[i++] = ft_strdup((*cmd_tmp)->value);
		(*cmd_tmp) = (*cmd_tmp)->next;
	}
}

t_cmd	*tokens_to_cmds(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*new_cmd;
	t_redir	*new;
	t_token	*cmd_tmp;

	head = NULL;
	while (tokens != NULL)
	{
		cmd_tmp = tokens;
		alloc_word(&tokens, &new_cmd);
		handle_redir(&cmd_tmp, &tokens, &new_cmd, &new);
		if (head == NULL)
			head = new_cmd;
		else
			tail->next = new_cmd;
		tail = new_cmd;
		if (tokens)
			tokens = tokens->next;
	}
	return (head);
}
