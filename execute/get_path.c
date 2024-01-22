#include "../minishell.h"

char	**get_path(void)
{
	char	*path;

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);
	return (ft_split(path, ':'));
}
