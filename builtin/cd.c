#include "../struct.h"

// cd 이후로 없음 && cd ~ -> home 으로 이동
// cd 경로 && cd ~/ ... -> 경로로 이동
// . -> 걍 똑같음
// ..
char *get_path(char *flag);

int	cd(char **cmd)
{
	if (cmd[0] == NULL)
		return (0);
	if (cmd[2] == 0 || ft_strncmp(cmd[2], "~", 1) != 0)
	{
		if (ft_strncmp(cmd[2], "~/", 2) != 0)
		{
			ft_strjoin(get_path("HOME"), &cmd[2][2]);
		}
		chdir(get_path("HOME"));

	}

char *get_path(char *flag)
{

}