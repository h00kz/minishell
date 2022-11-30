/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:11:13 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/11/30 16:16:01 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_envp	*lstnew_envp(char *variable, char *value)
{
	t_envp	*new_node;

	new_node = malloc(sizeof(t_envp) * 1);
	if (!new_node)
		return (NULL);
	new_node->variable = variable;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_cmds	*lstnew_cmd(t_cmds)