#include "minishell.h"

// execute flow
// check_heredoc
// 	 heredoc_cnt == 0 ->return
//	 heredoc_cnt != 0 -> heredoc infile 변경, heredoc 동작처리
// (pipe 개조)
// init_exec
//   get_path, get_env(2차원 배열로 들고있기)
// dup(stdin), dup(stdout)
// single process
//   if (check_builtin == true) 실행 후 종료
//   if (check_builtin == false) fork 후 실행하고 종료
// double process
// -> pipex


int main(int ac, char *av[], char *envp[])
{
	char	*str;
	t_shell	shell_info;

	init_env(&shell_info.env, envp);
	while (TRUE)
	{
		str = readline("minivell$ ");
		if (!str)
			return (0);
		add_history(str);
		free(str);
	}
	//	text code
	t_env *current_env;

	current_env = shell_info.env;
	while (current_env != NULL) {
		printf("Key: %s, Value: %s\n", current_env->key, current_env->value);
		current_env = current_env->next;
	}
	(void) ac;
	(void) av;
	(void) envp;
	return 0;
}