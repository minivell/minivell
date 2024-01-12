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

//
//#include <unistd.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//
//#define BUFFER_SIZE 1024
//
//void	cd(char **args)
//{
//	char	*home_dir;
//	char	*old_dir;
//	char	buffer[BUFFER_SIZE];
//
//	old_dir = getcwd(buffer, sizeof(buffer));
//	if (args[1] == NULL || strcmp(args[1], "~") == 0)
//	{
//		home_dir = getenv("HOME");
//		if (chdir(home_dir) != 0)
//			printf("cd: no such file or directory: %s\n", home_dir);
//	}
//	else if (strcmp(args[1], "-") == 0)
//	{
//		printf("%s\n", old_dir);
//		if(chdir(old_dir) != 0)
//			printf("cd: no such file or directory: %s\n", old_dir);
//	}
//	else
//	{
//		if (chdir(args[1]) != 0)
//			printf("cd: no such file or directory: %s\n", args[1]);
//	}
//}


// 폴더 없을 때 처리하기
// 폴더 안에 폴더 만들고 상위 폴더 삭제시 다 삭제