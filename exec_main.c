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


char	**get_path(t_exec *exec_info)
{
	t_env	*node;

//	if (!envp)
//		error_handle(6);
	node = exec_info->env;
	while (node)
	{
		if (!ft_strncmp(node->key, "PATH", 4))
			break ;
		node = node->next;
	}
	return (ft_split((char const *)node->value, ':'));
}


void	init_exec(t_shell *shell_info, t_exec *exec_info)
{
	exec_info->env = shell_info->env;
	exec_info->path = get_path(exec_info);
}


int	execute(t_shell *shell_info)
{
	t_exec exec_info;

	// 일단 minivell 에서 pipe가 돌아가게 만들기
	init_exec(shell_info, &exec_info);

//	exec_info.new_env = make_new_env(&exec_info);
	return 0;
}



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
		execute(&shell_info);
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