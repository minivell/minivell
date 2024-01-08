#include "../minishell.h"

void	echo(char **args)
{
	int	idx;
	int	newline;

	idx = 1;
	newline = TRUE;
	while (args[idx] && ft_strncmp(args[idx], "-n ", 3) == TRUE)
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
	if (newline == FALSE)
		printf("\n");
}