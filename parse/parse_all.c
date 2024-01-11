#include "../minishell.h"

int	parse_all(t_shell *shell_info, char *str)
{
	t_token *token;
	token = NULL;
	shell_info->heredoc_cnt = 0;
	if (error_before_parse(token, str) == EXIT_FAILURE)
    	return (EXIT_FAILURE);
	parse_pipe(&token, str);
	parse_redir(&token);
	parse_space(&token);
	parse_filename(&token);
	
	// shell_info->heredoc_cnt = 0;
	// shell_info->pipe_cnt = 0;

	count_token_type(shell_info, token);
	// printf("heredoc: %d, pipe: %d\n", shell_info->heredoc_cnt, shell_info->pipe_cnt);

	// if (!token || token_error(token) != EXIT_SUCCESS)
	// {
	// 	free_token(token);
	// 	return (EXIT_FAILURE);
	// }

	// if (!token || error_before_parse(shell_info, token, str))
	// {
	// 	printf("%d\n", shell_info->heredoc_cnt);
	// 	free_token(token);
	// 	return (EXIT_FAILURE);
	// }
	t_token *current_token;
	current_token = token;
    while (current_token)
    {
        printf("Type: %d, Value: [%s]\n", current_token->type, current_token->value);
        current_token = current_token->next;
    }

	// parse_quote(&token);

	// token test code
	
	
	// 5. token 순회하면서 invalid token 삭제
	// 6. token 없거나 에러 걸리면 token free하고 fail return -> 나중에
	// 7. envp update -> 은영 실행부에서
	// 8. cmd init
	// init_cmd(&shell_info->cmd, token);
	// 9. cmd argument 합치기

	//  shell_info->cmd = tokens_to_cmds(token);

//	if (cmd != NULL)
//    {
//        printf("Command Arguments Count: %d\n", cmd->cmd_cnt);
//        for (int i = 0; i < cmd->cmd_cnt; i++)
//        {
//            printf("Argument %d: %s\n", i, cmd->cmd_args[i]);
//        }
//    }

//	printf("cmd: %s\n", shell_info->cmd->cmd_args[0]);
//	printf("cmd: %s\n", shell_info->cmd->cmd_args[1]);
	
	return (SUCCESS);
}
