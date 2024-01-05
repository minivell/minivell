#include "../minishell.h"

void add_token_if_not_empty(char **start, char **current, t_token **token, t_type type)
{
    if (*current != *start)
    {
        char *value = ft_strndup(*start, *current - *start);
        token_add_back(token, token_new_node(type, value));
    }
}

t_token	*token_new_node(t_type type, char *value)
{
	t_token	*node;

	node = ft_calloc(1, sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = value;
	node->token_flag = TRUE;
	node->next = NULL;
	return (node);
}

void	token_add_back(t_token **node, t_token *new)
{
	t_token	*tmp;

	if (!(*node))
		*node = new;
	else
	{
		tmp = *node;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	if (token == NULL)
		return ;
	while (token)
	{
		tmp = token->next;
		free (token->value);
		free (token);
		token = tmp;
	}
}

