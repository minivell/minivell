#include "../minishell.h"

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


//첫 child, 중간 child, 마지막 child, 명령어 실행



int	execute(t_shell *shell_info)
{
	t_exec exec_info;

	// 일단 minivell 에서 pipe가 돌아가게 만들기
	init_exec(shell_info, &exec_info);
	if (shell_info->pipe_cnt == 0)
		return 0;
//		single_process(shell_info, &exec_info);
	else
	{
		printf("shell_info->pipe_cnt: %d\n", shell_info->pipe_cnt);
		multi_process(shell_info, &exec_info);
	}
	return 0;
}