#include "../minishell.h"

t_cmd *tokens_to_cmds(t_token *tokens)
{
    t_cmd *head_cmd = NULL;
    t_cmd *current_cmd = NULL;

    while (tokens != NULL)
    {
        if (tokens->type == PIPE || current_cmd == NULL)
        {
            t_cmd *new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
            if (!new_cmd)
            {
                while (head_cmd != NULL)
                {
                    t_cmd *temp = head_cmd;
                    head_cmd = head_cmd->next;
                    free(temp);
                }
                return NULL;
            }

            new_cmd->cmd_args = NULL;
            new_cmd->cmd_cnt = 0;
            new_cmd->redir = NULL;
            new_cmd->next = NULL;

            if (head_cmd == NULL)
                head_cmd = new_cmd;
            else
                current_cmd->next = new_cmd;

            current_cmd = new_cmd;

            if (tokens->type == PIPE)
            {
                tokens = tokens->next; // 파이프 토큰을 건너뛰기
                continue;
            }
        }

        // 현재 토큰을 현재 커맨드의 인자 배열에 추가
        current_cmd->cmd_args = realloc(current_cmd->cmd_args, sizeof(char *) * (current_cmd->cmd_cnt + 1));
        if (!current_cmd->cmd_args)
        {
            // 메모리 재할당 실패시, 할당된 모든 구조체 해제
            while (head_cmd != NULL)
            {
                t_cmd *temp = head_cmd;
                head_cmd = head_cmd->next;
                free(temp);
            }
            return NULL;
        }

        current_cmd->cmd_args[current_cmd->cmd_cnt] = ft_strdup(tokens->value);
        current_cmd->cmd_args[current_cmd->cmd_cnt + 1] = NULL;
        current_cmd->cmd_cnt++;

        tokens = tokens->next; // 다음 토큰으로 이동
    }

    return head_cmd; // 첫 번째 커맨드 구조체 반환
}

// t_cmd *tokens_to_cmds(t_token *tokens)
// {
// 	t_cmd *cmd = (t_cmd *)malloc(sizeof(t_cmd));
// 	if (!cmd)
// 	{
// 		return NULL;
// 	}

// 	cmd->cmd_args = NULL; // 커맨드 인자 배열 초기화
// 	cmd->cmd_cnt = 0; // 커맨드 카운트 초기화
// 	cmd->next = NULL; // 다음 커맨드 포인터 초기화

//   t_token *current_token = tokens; // 현재 처리 중인 토큰
//   while (current_token != NULL)
//     {
//         // 현재 토큰을 커맨드 인자 배열에 추가
//         cmd->cmd_args = realloc(cmd->cmd_args, sizeof(char *) * (cmd->cmd_cnt + 1));
//         if (!cmd->cmd_args)
//         {
//             // 메모리 재할당 오류 처리
//             free(cmd);
//             return NULL;
//         }
//         cmd->cmd_args[cmd->cmd_cnt] = ft_strdup(current_token->value);
//         cmd->cmd_cnt++;

// 		current_token = current_token->next; // 다음 토큰으로 이동
// 	}

// 	return cmd; // 완성된 커맨드 반환
// }

// void	init_cmd(t_cmd **cmd, t_token *token)
// {
//     return ;
// }
