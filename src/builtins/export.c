#include "../../inc/minishell.h"

static void ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static t_envp *sort_ascii(t_envp *a, t_envp *b)
{
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
}

static void print_env(t_envp *envp)
{
	t_envp  *a;
	t_envp  *b;
	t_envp  *save;

	a = envp;
	b = envp;
	save = envp;
	envp = sort_ascii(a, b);
	while (save)
	{
		ft_putstr_fd("declare -x ", 1);
		printf("%s=\"%s\"\n", save->variable, save->value);
		save = save->next;
	}
}

int ft_export(char **argv, char *opt, t_cmds *cmds)
{
	char *opt_tmp;
	t_envp *export_lst;

	if (*opt)
		opt_tmp = ft_strtrim(opt, " ");
	if (!*argv && !*opt)
	{
		print_env(cmds->lst_envp);
	}
	else if (opt_tmp[0] != 0)
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(opt_tmp, 2);
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
			}
			argv++;
		}
	}
	if (opt_tmp)
		free(opt_tmp);
	return (g_exit_code);
}