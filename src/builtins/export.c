/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:24:43 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/01/13 11:24:43 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_env(t_envp *envp, int fd)
{
	t_envp	*save;
	char	*first_ascii;

	save = envp;
	while (ft_check_print(envp) == 0)
	{
		ft_putstr_fd("declare -x ", fd);
		first_ascii = get_first_ascii(envp);
		save = ft_find_node(first_ascii, envp);
		if (save->value)
		{
			ft_putstr_fd(save->variable, fd);
			ft_putchar_fd('=', fd);
			ft_putendl_fd(save->value, fd);
		}
		else
			ft_putendl_fd(save->variable, fd);
		save->print = 1;
	}
}

static void	ft_error(char **argv)
{
	g_exit_code[0] = 2;
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(*argv, 2);
	ft_putendl_fd(": not a valid identifier", 2);
}

void	ft_dans_le_cul(int sep_i, char **argv, int i, t_cmds *cmd)
{
	if (argv[i][sep_i - 1] == '+')
		lstadd_back_envp(&cmd->lst_envp, lstnew_envp(\
			ft_strndup(argv[i], sep_i - 1), ft_strdup(&argv[i][sep_i + 1])));
	else
		lstadd_back_envp(&cmd->lst_envp, lstnew_envp(ft_strndup(argv[i], sep_i),
				ft_strdup(&argv[i][sep_i + 1])));
}

static void	make_export(t_cmds *cmd, char **argv, int sep_i)
{
	int	i;

	i = -1;
	while (argv[++i])
	{		
		if (!ft_export_isalnum(argv[i]))
		{
			ft_error(argv);
			break ;
		}
		if (ft_check_double_var(cmd->lst_envp, argv[i]) == 1)
		{
			if (ft_str_index_chr(argv[i], '=') < 0)
				lstadd_back_envp(&cmd->lst_envp, \
					lstnew_envp(ft_strdup(argv[i]), 0));
			else
			{
				sep_i = ft_str_index_chr(argv[i], '=');
				ft_dans_le_cul(sep_i, argv, i, cmd);
			}
		}
	}
}

int	ft_export(char **argv, char *opt, t_cmds *cmd, int fd)
{
	if (!*argv && !*opt)
		print_env(cmd->lst_envp, fd);
	else if (*opt)
	{
		g_exit_code[0] = 1;
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(opt, 2);
		ft_putendl_fd(": invalid option", 2);
	}
	else
		make_export(cmd, argv, 0);
	return (g_exit_code[0]);
}
