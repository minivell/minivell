#include "../minishell.h"

int check_quote(t_quote *quote, char c)
{
    if (quote->quote_flag == FALSE && (c == '\'' || c == '\"'))
    {
        quote->quote_flag = TRUE;
        quote->quote = c;
    }
    else if (quote->quote_flag == TRUE && c == quote->quote)
    {
        quote->quote_flag = FALSE;
    }
    return (quote->quote_flag);
}

// void 	parse_quote(t_token **token)
// {
//     return ;
// }
