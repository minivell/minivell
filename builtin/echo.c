#include "../minishell.h"

int	echo(char **args)
{
	int	idx;
	int	newline;

	idx = 1;
	newline = TRUE;
	while (args[idx] && ft_strcmp(args[idx], "-n") == 0)
	{
		newline = FALSE;
		idx++;
	}
	while (args[idx])
	{
		printf("%s", args[idx]);
		if (args[idx + 1])
			printf(" ");
		idx++;
	}
	if (newline == TRUE)
		printf("\n");
	return (SUCCESS);
}
