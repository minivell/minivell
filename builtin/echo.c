#include "../minishell.h"

// -nnnnnnn -> 정상작동 처리
// -n -n -n -n -n -> 정상작동 처리
// -n-n-n-n-n-n -> 그냥 하나의 문자열로 처리
void	echo(char **args)
{
	int	idx;
	int	newline;

	idx = 1;
	newline = TRUE;
	if (args[idx] && ft_strncmp(args[idx], "-n", 2) == TRUE)
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