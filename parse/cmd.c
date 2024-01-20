#include "../minishell.h"

void	free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir != NULL)
	{
		tmp = redir->next;
		free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

void	free_str_arr(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free_str_arr(cmd->cmd_args);
		free_redir_list(cmd->redir);
		free(cmd);
		cmd = tmp;
	}
}
int count_cmd_args(t_token *tokens) {
	int cnt = 0;
	while (tokens != NULL && tokens->type != PIPE) {
		if (tokens->type == WORD) {
			cnt++;
		}
		tokens = tokens->next;
	}
	return cnt;
}

void process_redirections(t_token **cmd_tmp, t_cmd *new_cmd) {
	t_redir *new;
	char *filename;

	while (*cmd_tmp && (*cmd_tmp)->type >= OUT_REDIR && (*cmd_tmp)->type <= HEREDOC) {
		filename = ft_strdup((*cmd_tmp)->next->value);
		new = new_redir((*cmd_tmp)->type, filename);
		add_back_redir(&(new_cmd->redir), new);
		*cmd_tmp = (*cmd_tmp)->next->next; // Move to next after redirection token
	}
}

t_cmd *create_new_cmd(t_token **cmd_tmp, int cnt) {
	t_cmd *new_cmd = ft_calloc(1, sizeof(t_cmd));
	new_cmd->cmd_args = ft_calloc(cnt + 1, sizeof(char *));
	new_cmd->cmd_cnt = cnt;

	for (int i = 0; i < cnt && *cmd_tmp; i++) {
		process_redirections(cmd_tmp, new_cmd);
		if ((*cmd_tmp)->type == WORD) {
			new_cmd->cmd_args[i] = ft_strdup((*cmd_tmp)->value);
			*cmd_tmp = (*cmd_tmp)->next;
		}
	}

	return new_cmd;
}

t_cmd *tokens_to_cmds(t_token *tokens) {
	t_cmd *head = NULL;
	t_cmd *tail = NULL;
	t_token *cmd_tmp;

	while (tokens != NULL) {
		cmd_tmp = tokens;
		int cnt = count_cmd_args(tokens);

		while (tokens != NULL && tokens->type != PIPE) {
			tokens = tokens->next;
		}

		t_cmd *new_cmd = create_new_cmd(&cmd_tmp, cnt);

		if (head == NULL) {
			head = new_cmd;
		} else {
			tail->next = new_cmd;
		}
		tail = new_cmd;

		if (tokens) {
			tokens = tokens->next;
		}
	}

	return head;
}