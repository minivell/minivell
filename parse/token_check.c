#include "../minishell.h"

int	check_pipe_error(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE && (!token->next || token->next->type == PIPE))
			return (print_error_msg());
		token = token->next;
	}
	return (EXIT_SUCCESS);
}

int	check_redir_sequence_error(t_token *token)
{
	while (token && token->next)
	{
		if ((token->type >= OUT_REDIR && token->type <= HEREDOC) && \
			(token->next->type >= OUT_REDIR && token->next->type <= HEREDOC))
			return (print_error_msg());
		token = token->next;
	}
	return (EXIT_SUCCESS);
}

int	check_heredoc_limit(t_token *token)
{
	int	heredoc_count;

	heredoc_count = 0;
	while (token)
	{
		if (token->type == HEREDOC)
			heredoc_count++;
		if (heredoc_count >= 16)
			return (print_error_msg());
		token = token->next;
	}
	return (EXIT_SUCCESS);
}

int	check_redir_filename_error(t_token *token)
{
	while (token)
	{
		if ((token->type >= OUT_REDIR && token->type <= HEREDOC) && \
			(!token->next || token->next->type != FILENAME))
			return (print_error_msg());
		token = token->next;
	}
	return (EXIT_SUCCESS);
}

int	validate_token(t_token **token)
{
	if (!token || !*token || (check_pipe_error(*token) != EXIT_SUCCESS))
	{
		free_token_list(*token);
		return (EXIT_FAILURE);
	}
	if (check_redir_sequence_error(*token) != EXIT_SUCCESS)
	{
		free_token_list(*token);
		return (EXIT_FAILURE);
	}
	if (check_heredoc_limit(*token) != EXIT_SUCCESS)
	{
		free_token_list(*token);
		return (EXIT_FAILURE);
	}
	if (check_redir_filename_error(*token) != EXIT_SUCCESS)
	{
		free_token_list(*token);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
