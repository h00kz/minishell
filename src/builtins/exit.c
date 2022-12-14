#include "../../inc/minishell.h"

static void exit_free(t_cmds *cmd, int exit_code)
{
	g_exit_code = exit_code;
	free_cmd(cmd);
	exit(g_exit_code);
}

int	ft_exit(char **argv, char *opt, t_cmds *cmd)
{
	int	i;

	i = 0;
	if (!*argv)
	{
		free_cmd(cmd);
		exit(g_exit_code);
	}
	else if (*argv[0] == '+' || *argv[0] == '-')
		i++;
	if ((int)ft_strlen(*argv) >= 19 || !ft_str_isdigits(&argv[0][i]))
	{
		ft_putendl_fd("NEED NUM ARG", 2);
		exit_free(cmd, 2);
	}
	if (argv[1] != NULL)
	{
		ft_putendl_fd("TOO MANY ARG", 2);
		g_exit_code = 1;
	}
	else
		exit_free(cmd, ft_atoi(&argv[0][i]) % 256);
}