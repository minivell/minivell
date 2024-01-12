#include "../minishell.h"

int	parse_all(t_shell *shell_info, char *str)
{
	t_token *token;
	token = NULL;
	init_shell(shell_info);
	if (error_before_parse(token, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	parse_pipe(&token, str);
	parse_redir(&token);
	parse_space(&token);
	parse_filename(&token);
	// 여기서 quote 뜯는 로직 추가해야 함
	append_redir_to_shell(shell_info, token);
	
	// 앞으로 구현해야 할 것
	// 5. token 순회하면서 invalid token 삭제 (token 없거나 에러 걸리면 token free하고 fail return)
	// 6. envp update -> 은영 실행부에서 처리
	// 7. cmd init 및 argument 저장
	count_token_type(shell_info, token);
	shell_info->cmd = tokens_to_cmds(token);

	///////////////////////////출력 확인 코드 모음///////////////////////////////

	///////////////token 출력 확인 코드////////////////////
	// t_token *current_token;
	// current_token = token;
    // while (current_token)
    // {
    //     printf("Type: %d, Value: [%s]\n", current_token->type, current_token->value);
    //     current_token = current_token->next;
    // }

	///////////////////redir 출력 확인 코드///////////////////////////
	t_redir *current_redir;
	current_redir = shell_info->redir;
	while (current_redir)
	{
		const char *filename = current_redir->filename ? current_redir->filename : "[NULL]";
		printf("Redirection Type: %d, Filename: %s\n", current_redir->type, filename);
		current_redir = current_redir->next;
	}

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

	return (SUCCESS);
}
