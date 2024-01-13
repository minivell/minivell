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

void remove_outer_quotes(t_token **token_tmp) 
{
    t_token *token = *token_tmp;
    while (token)
    {
        char *str = token->value;
        int len = ft_strlen(str);
        char *new_str = malloc(len + 1);
        int new_index = 0;
        for (int i = 0; i < len; i++) 
        {
            if (str[i] == '\"' || str[i] == '\'') 
            {
                char quote_type = str[i];
                int j = i + 1;
                while (j < len && str[j] != quote_type) 
                    j++;
                if (j < len) 
                {
                    i++;
                    while (i < j) 
                        new_str[new_index++] = str[i++];
                } 
                else 
                    new_str[new_index++] = str[i];
            } 
            else 
                new_str[new_index++] = str[i];
        }
        new_str[new_index] = '\0';
        strlcpy(str, new_str, len + 1);
        free(new_str);
        token = token->next;
    }
}
