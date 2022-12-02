/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:16:09 by pdubacqu          #+#    #+#             */
/*   Updated: 2022/12/02 17:49:11 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmds	*parse_input(char *input, char **envp)
{
	char	**input_split;
	t_cmds	*cmd;
	int	i;

	i = 0;
	if (ft_strncmp(input, "exit", 4) == 0)
		exit(0);
	input_split = ft_split(input, ' ');
	cmd = lstnew_cmd(input_split, envp);
	free(input_split);
	return (cmd);
}
