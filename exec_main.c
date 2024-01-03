#include "minishell.h"

int main(int ac, char *av[], char *envp[])
{
	char	*str;

	while (TRUE)
	{
		str = readline("minivell$ ");
		if (!str)
			return (0);
		add_history(str);
		free(str);
	}
	(void) ac;
	(void) av;
	(void) envp;
	return 0;
}