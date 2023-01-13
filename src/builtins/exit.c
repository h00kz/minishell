/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:24:49 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/01/13 11:24:49 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	exit_free(t_cmds *cmd, int exit_code)
{
	g_exit_code[0] = exit_code;
	free_cmd(cmd);
	exit(g_exit_code[0]);
}

static void	ft_check_overflow(char **argv, char *opt, t_cmds *cmd, int i)
{
	if (!*argv && ((int)ft_strlen(opt) > 20
			|| ft_strncmp(opt, "-9223372036854775809", 20) >= 0
			|| !ft_str_isdigits(&opt[1])))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(opt, 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit_free(cmd, 2);
	}
	else if (!*opt && ((int)ft_strlen(*argv) > 19
			|| ft_strcmp(*argv, "9223372036854775807") >= 0
			|| !ft_str_isdigits(&argv[0][i])))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(*argv, 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit_free(cmd, 2);
	}
}

static void	exit_opt_err(char **argv, char *opt, int i, t_cmds *cmd)
{
	ft_check_overflow(argv, opt, cmd, i);
	if (!*opt && argv[1] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_exit_code[0] = 1;
	}
	else
	{
		if (*opt && !*argv)
			exit_free(cmd, (ft_atoi(opt) % 256));
		else
			exit_free(cmd, (ft_atoi(&argv[0][i]) % 256));
	}
}

int	ft_exit(char **argv, char *opt, t_cmds *cmd)
{
	int	i;

	i = 0;
	if (!*argv && !*opt)
		exit(g_exit_code[0]);
	else if (*argv)
		if (*argv[0] == '+' && !*opt)
			i++;
	exit_opt_err(argv, opt, i, cmd);
	return (2);
}
