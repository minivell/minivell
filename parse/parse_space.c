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
    t_quote quote;
    quote.quote_flag = FALSE;

    while (tmp)
    {
        char *str = tmp->value;
        while (*str)
        {
            char *start = str;
            if (!quote.quote_flag && ft_isspace(*str))
            {
                str++;
                continue;
            }
            if (*str == '\'' || *str == '\"')
            {
                check_quote(&quote, *str);
                start = str;
                str++;
                while (*str && (quote.quote_flag && *str != quote.quote))
                {
                    str++;
                }
                if (quote.quote_flag && *str == quote.quote)
                {
                    check_quote(&quote, *str);
                    str++;
                }
            }
            else
            {
                while (*str && !ft_isspace(*str))
                {
                    str++;
                }
			}
            if (str > start)
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
