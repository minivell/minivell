#include "../minishell.h"

int print_error_msg(void)
{
	ft_putstr_fd("minivell: syntax error\n", 2);
	g_exit_code = 258;
	return (EXIT_FAILURE);
}

int quote_error(char *str)
{
	t_quote q;

	q.quote_flag = FALSE;
	while (*str)
	{
		check_quote(&q, *str);
		str++;
	}
	if (q.quote_flag == TRUE)
	{
		if (q.quote == '\'' || q.quote == '\"')
			return (print_error_msg());
	}
	return (EXIT_SUCCESS);
}

int token_error(t_token *token)
{
	t_token	*tmp;

	if (token->type == PIPE)
		return (print_error_msg());
	tmp = token;
	while (tmp->next)
	{
		if (((IN_REDIR <= tmp->type && tmp->type <= APPEND_REDIR) && tmp->next->type != WORD)
			|| (tmp->type == PIPE && tmp->next->type == PIPE))
			return (print_error_msg());
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (IN_REDIR <= tmp->type && tmp->type <= APPEND_REDIR)
			return (print_error_msg());
		else if (tmp->type == PIPE)
			return (print_error_msg());
	}
	return (EXIT_SUCCESS);
}

