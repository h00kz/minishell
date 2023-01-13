/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:24:54 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/01/13 11:24:55 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_exit_perror(char *msg, char *av, int exit_code)
{
	g_exit_code[0] = exit_code;
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(av, 2);
	ft_putendl_fd(msg, 2);
	return (exit_code);
}

char	**ft_cpy_envp(char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc((i + 1) * sizeof(char *));
	new_envp[i] = NULL;
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (new_envp);
}

int	ft_env(char **argv, char *opt, t_cmds *cmd, int fd)
{
	int	i;

	i = 0;
	g_exit_code[0] = 0;
	update_cmds_env(cmd);
	if (!*argv && !*opt)
	{
		while (cmd->envp[i] != NULL)
		{
			if (ft_str_index_chr(cmd->envp[i], '=') != -1)
				ft_putendl_fd(cmd->envp[i], fd);
			i++;
		}
		return (0);
	}
	if (*opt)
		return (ft_exit_perror(": Invalid option", opt, 125));
	else if (*argv)
		return (ft_exit_perror(": No such file or directory", argv[0], 127));
	return (0);
}
