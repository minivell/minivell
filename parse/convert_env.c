#include "../minishell.h"

int convert_env_len(char *str, int i)
{
	int len;

	len = 0;
	while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '\"' && str[i] != '\'' && str[i] != '\\')
	{
		if (str[i] == '\0')
			return (len);
		len++;
		i++;
	}
	return (len);
}
