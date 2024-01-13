#include "../minishell.h"

int	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (EXIT_FAILURE);
	printf("%s\n", pwd);
	free (pwd);
	return (SUCCESS);
}
