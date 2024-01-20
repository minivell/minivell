#include "../minishell.h"

void parse_pipe(t_token **token, char *str)
{
	t_quote quote;
	char *tmp;
	
	tmp = str;
	quote.quote_flag = FALSE;
	while (*str)
	{
		if (check_quote(&quote, *str) == FALSE && quote.quote_flag == FALSE)
		{
			if (*str == '|')
			{
				if (str > tmp)
					add_token_if_not_empty(&tmp, &str, token, WORD);
				add_back_token(token, new_token(PIPE, ft_strdup("|")));
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
