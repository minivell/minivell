#include "../minishell.h"

void	hrd_handler(int sig_no)
{
	(void) sig_no;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	exit (EXIT_FAILURE);
}

void	hrd_ign_handler(int sig_no)
{
	(void) sig_no;
	g_exit_code = 1;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signal(int sig_int, int sig_quit)
{
	if (sig_int == DEFAULT)
		signal(SIGINT, SIG_DFL);
	if (sig_int == IGNORE)
		signal(SIGINT, SIG_IGN);
	if (sig_int == HRD_IGN)
		signal(SIGINT, hrd_ign_handler);
	if (sig_int == HRD_CHILD)
		signal(SIGINT, hrd_handler);
	if (sig_quit == DEFAULT)
		signal(SIGQUIT, SIG_DFL);
	if (sig_quit == IGNORE || sig_quit == HRD_IGN || sig_quit == HRD_CHILD)
		signal(SIGQUIT, SIG_IGN);
}
