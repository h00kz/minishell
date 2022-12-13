#include "../../inc/minishell.h"

static int	ft_echo_opt(char *opt)
{
	int		i;
	char	*tmp;

	i = 1;
	tmp = ft_strtrim(opt, " ");
	if (tmp[0] == '-')
	{
		while (tmp[i])
		{
			if (tmp[i] != 'n')
			{
				free(tmp);
				return (0);
			}
			i++;
		}
	}
	free(tmp);
	return (1);
}

static void	ft_pecho(char **argv)
{
	int i;

	i = 0;
	if (!ft_strncmp(argv[i], "$?", 2))
	{
		ft_putnbr_fd(g_exit_code, 1);
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
}

int ft_echo(char **argv, char *opt, t_cmds *cmds)
{

	if (!*argv && !*opt)
	{
		ft_putendl_fd("", 1);
		return (1);
	}
	else if (*argv && !*opt)
	{
		ft_pecho(argv);
		ft_putendl_fd("", 1);
		return (1);
	}
	else if (!*argv && ft_echo_opt(opt))
		return (1);
	else if (!*argv && !ft_echo_opt(opt))
	{
		ft_putstr_fd(opt, 1);
	}
	else if (*argv && !ft_echo_opt(opt))
	{
		ft_putstr_fd(opt, 1);
		ft_pecho(argv);
		ft_putendl_fd("", 1);
		return (1);
	}
	else if (*argv && ft_echo_opt(opt))
	{
		ft_pecho(argv);
		return (1);
	}
	return (0);
}