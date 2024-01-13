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
            new_cmd->cmd_args = (char **)malloc(sizeof(char *));  // NULL 포인터를 위한 공간 할당
            new_cmd->cmd_args[0] = NULL;  // 첫 번째 요소를 NULL로 초기화
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
                tokens = tokens->next;
                continue;
            }
        }

        // 리다이렉션 토큰을 처리합니다
        if (tokens->type >= OUT_REDIR && tokens->type <= HEREDOC)
        {
            if (tokens->next && tokens->next->type == FILENAME)
            {
                char *filename = ft_strdup(tokens->next->value);
                t_redir *new = new_redir(tokens->type, filename);
                add_back_redir(&(current_cmd->redir), new);
                tokens = tokens->next;  // 파일 이름 토큰을 건너뜁니다
            }
        }
        else
        {
            char **new_args = (char **)malloc(sizeof(char *) * (current_cmd->cmd_cnt + 2));  // +1 개의 인자와 NULL을 위한 공간

            // 기존 인자 복사
            if (current_cmd->cmd_args)
            {
                ft_memcpy(new_args, current_cmd->cmd_args, sizeof(char *) * current_cmd->cmd_cnt);
                free(current_cmd->cmd_args);
            }

            new_args[current_cmd->cmd_cnt] = ft_strdup(tokens->value);
            new_args[current_cmd->cmd_cnt + 1] = NULL;  // 배열의 끝에 NULL 추가

            current_cmd->cmd_args = new_args;
            current_cmd->cmd_cnt++;
        }

        tokens = tokens->next;
    }

    return head_cmd;
}
