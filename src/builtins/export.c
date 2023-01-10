#include "../../inc/minishell.h"

t_envp	*get_first_ascii(t_envp *envp)
{
	t_envp	*save;

	save = envp;
	while (envp)
	{
		if (ft_strcmp(save->variable, envp->variable) > 0 && envp->print == 0)
		{
			save = envp;
			save->print = 1;
		}
		envp = envp->next;
	}
	return (save);
}

int	ft_check_print(t_envp *envp)
{
	while (envp)
	{
		if (envp->print == 0)
			return (0);
		envp = envp->next;
	}
	return (1);
}

static void print_env(t_envp *envp)
{
	t_envp  *save;

	save = envp;
	while (ft_check_print(envp) == 0)
	{
		ft_putstr_fd("declare -x ", 1);
		save = get_first_ascii(envp);
		if (save->value)
			printf("%s=\"%s\"\n", save->variable, save->value);
		else
			printf("%s", save->variable);
	}
}

int ft_export(char **argv, char *opt, t_cmds *cmds)
{
	if (!*argv && !*opt)
	{
		print_env(cmds->lst_envp);
	}
	else if (*opt)
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(opt, 2);
		ft_putendl_fd(": invalid option", 2);
	}
	else
	{
		while (*argv)
		{		
			if (!ft_export_isalnum(*argv))
			{
				g_exit_code = 2;
				ft_putstr_fd("minishell: export: ", 2);
				ft_putstr_fd(*argv, 2);
				ft_putendl_fd(": not a valid identifier", 2);
				break ;
			}
			argv++;
		}
	}
	return (g_exit_code);
}