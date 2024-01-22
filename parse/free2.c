#include "../minishell.h"

void free_cmd_list(t_cmd *cmd)
{
	t_cmd *tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free_str_arr_line(cmd->cmd_args, cmd->cmd_cnt);
		free_redir_list(cmd->redir);
		free(cmd);
		cmd = tmp;
	}
}


void free_token_list(t_token *token)
{
	t_token *tmp;
	if (token == NULL)
		return ;
	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
}

void free_env_list(t_env *env)
{
	t_env *tmp;

	while (env != NULL)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}