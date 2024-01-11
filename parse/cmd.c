#include "../minishell.h"

// t_token 리스트를 t_cmd 리스트로 변환하는 함수
t_cmd *tokens_to_cmds(t_token *tokens)
{
    t_cmd *cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd)
    {
        return NULL;
    }

    cmd->cmd_args = NULL; // 커맨드 인자 배열 초기화
    cmd->cmd_cnt = 0; // 커맨드 카운트 초기화
    cmd->next = NULL; // 다음 커맨드 포인터 초기화

    t_token *current_token = tokens; // 현재 처리 중인 토큰
    while (current_token != NULL)
    {
        // 현재 토큰을 커맨드 인자 배열에 추가
        cmd->cmd_args = realloc(cmd->cmd_args, sizeof(char *) * (cmd->cmd_cnt + 1));
        if (!cmd->cmd_args)
        {
            // 메모리 재할당 오류 처리
            free(cmd);
            return NULL;
        }
        cmd->cmd_args[cmd->cmd_cnt] = ft_strdup(current_token->value);
        cmd->cmd_cnt++;

        current_token = current_token->next; // 다음 토큰으로 이동
    }

    return cmd; // 완성된 커맨드 반환
}

// void	init_cmd(t_cmd **cmd, t_token *token)
// {
//     return ;
// }