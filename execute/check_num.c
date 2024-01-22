int	check_num(char *str)
{
	while (*str)
	{
	if (!('0' <= *str && *str <= '9'))
	return (0);
	str++;
	}
	return (1);
}