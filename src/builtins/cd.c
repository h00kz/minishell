#include "../../inc/minishell.h"

int	ft_cd(char *argv)
{
	const char	*home;

	if (!argv)
	{
		home = getenv("HOME");
		if (chdir(home) < 0)
		{
			perror("cd");
			return (1);
		}
	}
	if (chdir(argv) < 0)
	{
		perror("cd");
		return (1);
	}
	else
	{
		
	}
	return (0);
}