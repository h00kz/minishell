#include "../../inc/minishell.h"

char	*get_first_ascii(t_envp *envp)
{
	char	*first_ascii;

	first_ascii = ft_calloc(sizeof(char *), 2);
	first_ascii[0] = 127;
	while (envp)
	{
		if (ft_strcmp(first_ascii, envp->variable) > 0 && envp->print == 0)
		{
			if (first_ascii[0] == 127)
				free(first_ascii);
			first_ascii = envp->variable;
		}
		envp = envp->next;
	}
	return (first_ascii);
}

int	ft_check_print(t_envp *envp)
{
	while (envp)
	{
		if (envp->print == 0)
			return (0);
		else
			envp = envp->next;
	}
	return (1);
}

t_envp	*ft_find_node(char *to_find, t_envp *envp)
{
	while (ft_strcmp(to_find, envp->variable) != 0 && envp)
		envp = envp->next;
	return (envp);
}

static void print_env(t_envp *envp)
{
	t_envp  *save;
	char	*first_ascii;

	save = envp;
	while (ft_check_print(envp) == 0)
	{
		ft_putstr_fd("declare -x ", 1);
		first_ascii = get_first_ascii(envp);
		save = ft_find_node(first_ascii, envp);
		if (save->value)
			printf("%s=\"%s\"\n", save->variable, save->value);
		else
			printf("%s", save->variable);
		save->print = 1;
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