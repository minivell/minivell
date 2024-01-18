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
            new_cmd->cmd_args = (char **)malloc(sizeof(char *));
            new_cmd->cmd_args[0] = NULL;
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
        if (tokens->type >= OUT_REDIR && tokens->type <= HEREDOC)
        {
            if (tokens->next && tokens->next->type == FILENAME)
            {
                char *filename = ft_strdup(tokens->next->value);
                t_redir *new = new_redir(tokens->type, filename);
                add_back_redir(&(current_cmd->redir), new);
                tokens = tokens->next;
            }
        }
        else
        {
            char **new_args = (char **)malloc(sizeof(char *) * (current_cmd->cmd_cnt + 2));
            if (current_cmd->cmd_args)
            {
                ft_memcpy(new_args, current_cmd->cmd_args, sizeof(char *) * current_cmd->cmd_cnt);
                free(current_cmd->cmd_args);
            }
            new_args[current_cmd->cmd_cnt] = ft_strdup(tokens->value);
            new_args[current_cmd->cmd_cnt + 1] = NULL;
            current_cmd->cmd_args = new_args;
            current_cmd->cmd_cnt++;
        }

        tokens = tokens->next;
    }
    return head_cmd;
}
