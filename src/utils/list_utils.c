/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:11:13 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/11/30 20:16:16 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmds	*ft_lstnew_node(void)
{
	t_cmds	*new_node;

	new_node = malloc(sizeof(t_cmds) * 1);
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back_cmd(t_cmds **lst, t_cmds *new)
{
	t_cmds	*current;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

t_cmds	*lstnew_cmd(char **input_split, char **envp)
{
	int		i;
	int		j;
	int		whats_next;
	t_cmds	*cmd;

	j = 0;
	cmd = malloc(sizeof(t_cmds) * 1);
	if (cmd == NULL)
		return (NULL);
	i = 0;
	if (ft_strcmp(input_split[0], "<")== 0)
	{
		cmd->redir = L_REDIR;
		cmd->file_name[0] = input_split[1];
		whats_next = CMD;
		i = 2;
	}	
	while (input_split[i] != NULL)
	{
		if (cmd->cmd != NULL && ft_strcmp(input_split[i], "<") == 0
			&& ft_strcmp(input_split[i], "<<") == 0
			&& ft_strcmp(input_split[i], "|") == 0
			&& ft_strcmp(input_split[i], ">") == 0
			&& ft_strcmp(input_split[i], ">>") == 0)
		{
			ft_lstadd_back_cmd(&cmd, ft_lstnew_node());
			cmd = cmd->next;
		}
		if (ft_strcmp(input_split[i], "<") == 0)
		{
			cmd->redir = L_REDIR;
			i++;
			whats_next = FILES;
		}
		else if (ft_strcmp(input_split[i], "<<") == 0)
		{
			cmd->redir = L_HEREDOC;
			i++;
			whats_next = FILES;
		}
		else if (ft_strcmp(input_split[i], "|") == 0)
		{
			cmd->redir = PIPE;
			i++;
			whats_next = CMD;
		}
		else if (ft_strcmp(input_split[i], ">") == 0)
		{
			cmd->redir = R_REDIR;
			i++;
			whats_next = FILES;
		}
		else if (ft_strcmp(input_split[i], ">>") == 0)
		{
			cmd->redir = R_HEREDOC;
			i++;
			whats_next = FILES;
		}
		if (cmd->cmd == NULL && whats_next == CMD)
		{
			cmd->cmd = input_split[i];
			i++;
		}
		if (cmd->cmd != NULL && whats_next == CMD)
		{
			cmd->args = input_split[i];
			whats_next = FILES;
			i++;
		}
		if (whats_next == FILES)
		{
			cmd->file_name[j] = input_split[i];
			j++;
		}
	}
}
