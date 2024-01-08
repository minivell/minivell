//void	ft_export(char **args)
//{
//	if (args[1] == NULL)
//	{
//		fprintf(stderr, "Expected argument to \"export\"\n");
//	}
//	else
//	{
//		char *key = strtok(args[1], "=");
//		char *value = strtok(NULL, "=");
//		if (setenv(key, value, 1) != 0)
//		{
//			perror("minishell");
//		}
//	}
//}
