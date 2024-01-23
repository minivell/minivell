/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:42:30 by gykoh             #+#    #+#             */
/*   Updated: 2024/01/23 13:42:31 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_redir(t_token **token)
{
	t_token	*tmp;
	t_token	*next_tmp;
	t_token	*new_token;

	tmp = *token;
	while (tmp)
	{
		next_tmp = tmp->next;
		if (tmp->type == WORD)
		{
			new_token = NULL;
			parse_and_extract_redir(&new_token, tmp->value);
			if (new_token)
			{
				replace_token(token, tmp, new_token);
				tmp = next_tmp;
				continue ;
			}
		}
		tmp = next_tmp;
	}
}

void	parse_filename(t_token **token)
{
	t_token	*tmp;
	t_token	*next_tmp;

	tmp = *token;
	while (tmp)
	{
		next_tmp = tmp->next;
		if ((tmp->type == IN_REDIR || tmp->type == OUT_REDIR \
			|| tmp->type == APPEND_REDIR || tmp->type == HEREDOC))
		{
			if (next_tmp && next_tmp->type == WORD)
				next_tmp->type = FILENAME;
		}
		tmp = next_tmp;
	}
}

void	replace_token(t_token **token_list, t_token *old, t_token *new)
{
	t_token	*prev;
	t_token	*current;
	t_token	*last_new;

	prev = NULL;
	current = *token_list;
	while (current != old)
	{
		prev = current;
		current = current->next;
	}
	if (prev)
		prev->next = new;
	else
		*token_list = new;
	last_new = new;
	while (last_new->next)
		last_new = last_new->next;
	last_new->next = old->next;
	free(old->value);
	free(old);
}

void	parse_and_extract_redir(t_token **token, char *str)
{
	char	*tmp;
	t_quote	q;

	tmp = str;
	q.quote_flag = FALSE;
	while (*str)
	{
		if (!check_quote(&q, *str) && (*str == '<' || *str == '>'))
		{
			if (str != tmp)
				add_back_token(token, new_token(WORD, \
					ft_strndup(tmp, str - tmp)));
			create_redir_token(token, &str);
			tmp = str;
		}
		else
			str++;
	}
	if (*tmp)
		add_back_token(token, new_token(WORD, ft_strdup(tmp)));
}

void	create_redir_token(t_token **token, char **str)
{
	if (**str == '<' && *(*str + 1) != '<')
	{
		(*str)++;
		add_back_token(token, new_token(IN_REDIR, ft_strdup("<")));
	}
	else if (**str == '<' && *(*str + 1) == '<')
	{
		(*str) += 2;
		add_back_token(token, new_token(HEREDOC, ft_strdup("<<")));
	}
	else if (**str == '>' && *(*str + 1) != '>')
	{
		(*str)++;
		add_back_token(token, new_token(OUT_REDIR, ft_strdup(">")));
	}
	else if (**str == '>' && *(*str + 1) == '>')
	{
		(*str) += 2;
		add_back_token(token, new_token(APPEND_REDIR, ft_strdup(">>")));
	}
}
