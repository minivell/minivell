#include "../minishell.h"

int	parse_all(t_shell *shell_info, char *str)
{
	t_token	*token;

	token = NULL;
	init_shell(shell_info);
	if (quote_error(str) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	parse_pipe(&token, str);
	parse_redir(&token);
	parse_space(&token);
	replace_env_in_token(shell_info->env, token);
	remove_outer_quotes(&token);
	parse_filename(&token);
	count_token_type(shell_info, token);
	if (validate_token(&token) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	shell_info->cmd = tokens_to_cmds(token);
	free_token_list(token);
	return (SUCCESS);
}
