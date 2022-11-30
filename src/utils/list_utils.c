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

void	lst_print(t_envp *lst)
{
	t_envp *cur;

	cur = lst;
	while (cur)
	{
		printf("VAR = %s VALUE = %s", cur->variable, cur->value);
		cur = cur->next;
	}
}

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

t_cmds	*lstnew_cmd(char **input_split, char **envp)
{
	int		i;
	t_cmds	*cmd;

	cmd = malloc(sizeof(t_cmds) * 1);
	if (cmd == NULL)
		return (NULL);
	i = 0;
	while (input_split[i] != NULL)
	{
		if (ft_strcmp(input_split[i], "<"))
			cmd->redir = L_REDIR;
		else if (ft_strcmp(input_split[i], "<<"))
			cmd->redir = L_HEREDOC;
		else if (ft_strcmp(input_split[i], "|"))
			cmd->redir = PIPE;
		else if (ft_strcmp(input_split[i], ">"))
			cmd->redir = R_REDIR;
		else if (ft_strcmp(input_split[i], ">>"))
			cmd->redir = R_HEREDOC;
	}
}

void	lstadd_back_envp(t_envp **lst, t_envp *new)
{
	t_envp	*current;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		current = lstlast_envp(*lst);
		current->next = new;
	}
}

t_envp	*lstlast_envp(t_envp *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}