#include "../minishell.h"

void parse_redir(t_token **token)
{
	t_token *tmp = *token;
	t_token *next_tmp;
	t_token *new_token;

	while (tmp)
	{
		next_tmp = tmp->next;

		if (tmp->token_flag && tmp->type == WORD)
		{
			new_token = NULL;
			parse_and_extract_redir(&new_token, tmp->value);
			if (new_token)
			{
				tmp->token_flag = FALSE;
				replace_token(token, tmp, new_token);
				tmp = next_tmp;
				continue;
			}
		}
		tmp = next_tmp;
	}
}

void parse_filename(t_token **token)
{
    t_token *tmp = *token;
    t_token *next_tmp;

    while (tmp)
    {
        next_tmp = tmp->next;

        if (tmp->token_flag && (tmp->type == IN_REDIR || tmp->type == OUT_REDIR ||
                                tmp->type == APPEND_REDIR || tmp->type == HEREDOC))
        {
            if (next_tmp && next_tmp->type == WORD)
            {
                next_tmp->type = FILENAME;
            }
        }
        tmp = next_tmp;
    }
}

void replace_token(t_token **token_list, t_token *old_token, t_token *new_tokens)
{
	t_token *prev = NULL;
	t_token *current = *token_list;
	while (current != old_token)
	{
		prev = current;
		current = current->next;
	}
	if (prev)
		prev->next = new_tokens;
	else
		*token_list = new_tokens;

	t_token *last_new = new_tokens;
	while (last_new->next)
		last_new = last_new->next;
	last_new->next = old_token->next;
	free(old_token->value);
	free(old_token);
}

void parse_and_extract_redir(t_token **token, char *str)
{
	char *tmp = str;
	t_quote q;
	q.quote_flag = FALSE;

	while (*str)
	{
		if (!check_quote(&q, *str) && (*str == '<' || *str == '>'))
		{
			if (str != tmp)
				add_back_token(token, new_token(WORD, ft_strndup(tmp, str - tmp)));
			
			create_redir_token(token, &str);
			tmp = str;
		}
		else
			str++;
	}
	if (*tmp)
		add_back_token(token, new_token(WORD, ft_strdup(tmp)));
}

void create_redir_token(t_token **token, char **str)
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

