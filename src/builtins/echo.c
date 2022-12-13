#include "../../inc/minishell.h"

static int	ft_echo_opt(char *opt)
{
	int	i;

	i = 1;
	if (opt[0] == '-')
	{
		while (opt[i])
		{
			if (opt[i] != 'n')
			{
				printf("COUCOU\n");
				ft_putstr_fd(opt, 1);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

// int	ft_check_echo(char *input_split)
// {
// 	int	i;

// 	i = 0;
// 	while (input_split[i])
// 	{
// 		if (input_split[i] != '-' && input_split[i] != 'n')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

int ft_echo(char **argv, char *opt, t_cmds *cmds)
{
	if (argv && *argv && !*opt)
	{
		if (!ft_strncmp(*argv, "$?", 2))
		{
			ft_putnbr_fd(g_exit_code, 1);
			if ((*argv) + 1 != NULL)
				ft_putstr_fd(" ", 1);
		}
		while (*argv)
		{
			ft_putstr_fd(*argv, 1);
			if ((*argv) + 1 != NULL)
				ft_putstr_fd(" ", 1);
			argv++;
		}
		ft_putendl_fd("", 1);
		return (1);
	}
	else if (argv && *argv && ft_echo_opt(opt))
	{
		if (!ft_strncmp(*argv, "$?", 2))
		{
			ft_putnbr_fd(g_exit_code, 1);
			if ((*argv) + 1 != NULL)
				ft_putstr_fd(" ", 1);
		}
		while (*argv)
		{
			ft_putstr_fd(*argv, 1);
			if (((*argv) + 1) != NULL)
				ft_putstr_fd("/", 1);
			argv++;
		}
		return (1);
	}
	return (0);
}