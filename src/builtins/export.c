#include "../../inc/minishell.h"

static void ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void print_env(t_envp *envp)
{
	t_envp  *a;
	t_envp  *b;
	t_envp  *save;

	a = envp;
	b = envp;
	save = envp;
	while (a)
	{
		b = a->next;
		while (b)
		{
			if (ft_strcmp(a->variable, b->variable) > 0)    
			{
				ft_swap(&a->variable, &b->variable);
				ft_swap(&a->value, &b->value);
			}
			b = b->next;
		}
		a = a->next;
	}
	while (save)
	{
		ft_putstr_fd("declare -x ", 1);
		printf("%s=\"%s\"\n", save->variable, save->value);
		save = save->next;
	}
}

int ft_export(char *argv, char *opt, t_cmds *cmds)
{
	if (!argv && !*opt)
	{
		print_env(cmds->lst_envp);
	}
	else if (!argv && opt[0] != 0)
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(opt, 2);
		ft_putendl_fd(": invalid option", 2);
		return (1);
	}
	else
	{
		if (!ft_export_isalnum(argv))
		{
			g_exit_code = 2;
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(argv, 2);
			ft_putendl_fd(": not a valid identifier", 2);
			return (2);
		}
	}
	return (0);
}