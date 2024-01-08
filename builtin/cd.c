//#include "../minishell.h"
//
//void	ft_cd(char **args)
//{
//	char *path;
//
//	if (args[1] == NULL)
//	{
//		path = getenv("HOME");
//		if (path == NULL)
//		{
//			fprintf(stderr, "Expected HOME environment variable to be set\n");
//			return;
//		}
//	}
//	else
//	{
//		path = args[1];
//	}
//
//	if (chdir(path) != 0)
//	{
//		perror("minishell");
//	}
//}
