#include "../minishell.h"

void	replace_env_in_line(char **line, t_env *env)
{
	int		i;
	int		start_idx;
	char	*key;
	char	*value;
	char	*tmp;

	i = 0;
	start_idx = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] != '\0')
		{
			start_idx = ++i;
			key = find_key(*line, &i, &start_idx);
			value = find_value(env, key, NULL);
			free(key);
			if (value == NULL)
				continue ;
			tmp = ft_strjoin_free(ft_substr(*line, 0, start_idx - 1), value);
			*line = ft_strjoin_free(tmp, *line + i);
			i = start_idx + ft_strlen(value) - 1;
		}
		i++;
	}
}
