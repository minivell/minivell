#include "../minishell.h"

int	parse_all(t_shell *shell_info, char *str)
{
	t_token *token;
	token = NULL;
	if (error_before_parse(token, str) == EXIT_FAILURE)
    	return (EXIT_FAILURE);
	parse_pipe(&token, str);
	parse_redir(&token);
	parse_space(&token);
	parse_filename(&token);
	count_token_type(shell_info, token);

	shell_info->cmd = tokens_to_cmds(token);

	// t_cmd 구조체 안의 내용 출력 확인 코드
	t_cmd *current_cmd = shell_info->cmd;
	int cmd_index = 0;
	while (current_cmd != NULL)
	{
		printf("Command %d: ", cmd_index);
		for (int i = 0; i < current_cmd->cmd_cnt; i++)
		{
			printf("Arg %d: [%s] ", i, current_cmd->cmd_args[i]);
		}
		printf("\n");
		current_cmd = current_cmd->next;
		cmd_index++;
	}


	// -> 여기서 달러, 리다이렉션 처리
	// -> 여기서 쿼트 처리
	
	// shell_info->heredoc_cnt = 0;
	// shell_info->pipe_cnt = 0;
	// printf("heredoc: %d, pipe: %d\n", shell_info->heredoc_cnt, shell_info->pipe_cnt);
	// if (!token || token_error(token) != EXIT_SUCCESS)
	// {
	// 	free_token(token);
	// 	return (EXIT_FAILURE);
	// }



	// t_token *current_token;
	// current_token = token;
    // while (current_token)
    // {
    //     printf("Type: %d, Value: [%s]\n", current_token->type, current_token->value);
    //     current_token = current_token->next;
    // }




	// 5. token 순회하면서 invalid token 삭제
	// 6. token 없거나 에러 걸리면 token free하고 fail return -> 나중에

	// 7. envp update -> 은영 실행부에서

	// 8. cmd init
	// init_cmd(&shell_info->cmd, token);

	// 9. cmd argument 합치기
	//  shell_info->cmd = tokens_to_cmds(token);

	return (SUCCESS);
}
