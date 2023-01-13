/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_some_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:26:21 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/01/13 11:26:21 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	ft_free_some_shit(char **input_split, t_cmds *cmd)
{
	ft_free_split(input_split);
	free_cmd(cmd);
}

void	ft_free_some_shit_2(char **input_split, int j, char *input, t_cmds *cmd)
{
	ft_nfree_split(input_split, j);
	free(input);
	free_cmd(cmd);
}

void	ft_free_some_shit_3(char *input, char **cmd_split)
{
	free(input);
	ft_free_split(cmd_split);
}

void	ft_free_some_shit4(char **input_split)
{
	ft_free_split(input_split);
}
