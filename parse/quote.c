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

int find_matching_quote(const char *str, int start_index, char quote_type)
{
	int len = ft_strlen(str);
	for (int j = start_index; j < len; j++)
	{
		if (str[j] == quote_type)
			return j;
	}
	return len;
}

void remove_quotes_from_string(char *str, char *new_str)
{
	int len = ft_strlen(str);
	int new_index = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			int j = find_matching_quote(str, i + 1, str[i]);
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
}

char	handle_quotes(char quote_flag, char current_char)
{
	if (current_char == '\'' || current_char == '\"')
	{
		if (quote_flag == 0)
			return (current_char);
		else if (quote_flag == current_char)
			return (0);
	}
	return (quote_flag);
}

void remove_outer_quotes(t_token **token)
{
	t_token *token_tmp = *token;
	while (token_tmp)
	{
		char *str = token_tmp->value;
		int len = ft_strlen(str);
		char *new_str = malloc(len + 1);
		remove_quotes_from_string(str, new_str);
		ft_strlcpy(str, new_str, len + 1);
		free(new_str);
		token_tmp = token_tmp->next;
	}
}
