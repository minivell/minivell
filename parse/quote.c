#include "../minishell.h"

int	set_quote(t_quote *quote, char c)
{
	if (quote->quote_flag == FALSE && (c == '\'' || c == '\"'))
	{
		quote->quote_flag = TRUE;
		quote->quote = c;
	}
	else
		quote->quote_flag = FALSE;
	return (quote->quote_flag);
}
