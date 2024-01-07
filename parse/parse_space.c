#include "../minishell.h"

int ft_isspace(int c)
{
	return (c == ' ' || c == '\t');
}

void parse_space(t_token **token)
{
	t_token *tmp = *token;
	t_token *new_token_list = NULL;
	t_token *new_node;

	while (tmp)
	{
		char *str = tmp->value;
		while (*str)
		{
			char *start = str;
			while (*str && !ft_isspace(*str))
				str++;
			if (str != start)
			{
				new_node = new_token(tmp->type, ft_strndup(start, str - start));
				add_back_token(&new_token_list, new_node);
			}
			while (*str && ft_isspace(*str))
				str++;
		}
		tmp = tmp->next;
	}
	free_token(*token);
	*token = new_token_list;
}
