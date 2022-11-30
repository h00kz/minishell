/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:21:06 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/11/30 15:46:47 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_envp	*save_envp(char **envp)
{
	t_envp	*lst;
	char	**var;
	int		i;
	int		j;

	lst = NULL;
	var = NULL;
	if (!*envp || !envp)
		return (NULL);
	while (envp[i])
	{
		var = ft_split(envp[i], '=');
		lstadd_back_envp(&lst, lstnew_envp(var[0], var[1]));
		free(*var);
		free(var);
		i++;
	}
	return (lst);
}