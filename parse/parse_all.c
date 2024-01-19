#include "../minishell.h"

int	parse_all(t_shell *shell_info, char *str)
{
	t_token *token;
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
	return (SUCCESS);

	///////////////////////////출력 확인 코드 모음///////////////////////////////

	///////////////token 출력 확인 코드////////////////////
//	t_token *current_token;
//	current_token = token;
//    while (current_token)
//    {
//        printf("Type: %d, Value: [%s]\n", current_token->type, current_token->value);
//        current_token = current_token->next;
//    }

	///////////////////redir 출력 확인 코드///////////////////////////
	// t_redir *current_redir;
	// current_redir = shell_info->cmd->redir;
	// while (current_redir)
	// {
	// 	const char *filename = current_redir->filename ? current_redir->filename : "[NULL]";
	// 	printf("Redirection Type: %d, Filename: %s\n", current_redir->type, filename);
	// 	current_redir = current_redir->next;
	// }

	/////////////////t_cmd 구조체 안의 내용 출력 확인 코드///////////////////////
	// t_cmd *current_cmd = shell_info->cmd;
	// int cmd_index = 0;
	// while (current_cmd != NULL)
	// {
	// 	printf("Command %d: ", cmd_index);
	// 	for (int i = 0; i < current_cmd->cmd_cnt; i++)
	// 	{
	// 		printf("Arg %d: [%s] ", i, current_cmd->cmd_args[i]);
	// 	}
	// 	printf("\n");
	// 	current_cmd = current_cmd->next;
	// 	cmd_index++;
	// }

	/////////////////////////heredoc, pipe 개수 확인 코드//////////////////////////////////
	// shell_info->heredoc_cnt = 0;
	// shell_info->pipe_cnt = 0;
	// printf("heredoc: %d, pipe: %d\n", shell_info->heredoc_cnt, shell_info->pipe_cnt);

	////////////////////token 관련 메모리 해제 로직 /////////////////////////////////
	// if (!token || token_error(token) != EXIT_SUCCESS)
	// {
	// 	free_token(token);
	// 	return (EXIT_FAILURE);
	// }
}
