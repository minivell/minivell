#include "../minishell.h"

void parse_pipe(t_token **token, char *str)
{
	t_quote quote;
	char *tmp;
	
	tmp = str;
	while (*str)
	{
		if (set_quote(&quote, *str) == FALSE)
		{
			if (*str == '|')
			{
				add_token_if_not_empty(&tmp, &str, token, WORD);
				token_add_back(token, token_new_node(PIPE, ft_strdup("|")));
				tmp = ++str;
			}
			else
				str++;
		}
		else
			str++;
	}
	add_token_if_not_empty(&tmp, &str, token, WORD);
}
