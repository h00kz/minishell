/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:11:13 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/12/02 15:49:57 by pdubacqu         ###   ########.fr       */
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
	new_node->cmd = ft_calloc(sizeof(char), 1);
	new_node->args = ft_calloc(sizeof(char), 1);
	new_node->file_name = ft_calloc(sizeof(char*), 10);
	return (new_node);
}

void	ft_lstadd_back_cmd(t_cmds **lst, t_cmds *new)
{
	t_cmds	*current;

	current = *(lst);
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

void	free_cmd(t_cmds *cmd)
{
	int		i;
	t_cmds	*tmp;

	while (cmd != NULL)
	{
		tmp = cmd;
		cmd = cmd->next;
		i = 0;
		if (tmp->args)
			free(tmp->args);
		if (tmp->cmd)
			free(tmp->cmd);
		while (tmp->file_name[i])
		{
			free(tmp->file_name[i]);
			i++;
		}
		free(tmp->file_name);
		free(tmp);
	}
}

t_cmds	*lstnew_cmd(char **input_split, char **envp)
{
	int		i;
	int		j;
	int		whats_next;
	t_cmds	*cmd;
	t_cmds	*save;

	j = 0;
	i = 0;
	whats_next = 100;
	cmd = ft_lstnew_node();
	save = cmd;
	if (cmd == NULL)
		return (NULL);
	if (ft_strcmp(input_split[0], "<")== 0)
	{
		cmd->redir = L_REDIR;
		cmd->file_name[0] = input_split[1];
		whats_next = CMD;
		i = 2;
	}
	while (input_split && input_split[i])
	{
		if (cmd && cmd->cmd && ft_strcmp(input_split[i], "|") == 0)
		{
			cmd->redir = PIPE;
			whats_next = CMD;
			ft_lstadd_back_cmd(&cmd, ft_lstnew_node());
			cmd = cmd->next;
			free(input_split[i]);
			i++;
		}
		if (cmd->cmd && (whats_next == CMD | whats_next == 100))
		{
			free(cmd->cmd);
			cmd->cmd = input_split[i];
			whats_next = ARGS_OR_FILE;
		}
		else if (input_split[i][0] == '-' && whats_next == ARGS_OR_FILE)
		{
			free(cmd->args);
			cmd->args = input_split[i];
			whats_next = FILES;
		}
		else if (whats_next == ARGS_OR_FILE || whats_next == FILES
		&& ft_strcmp(input_split[i], "<") != 0
		&& ft_strcmp(input_split[i], "<<") != 0
		&& ft_strcmp(input_split[i], ">") != 0
		&& ft_strcmp(input_split[i], ">>") != 0)
		{
			cmd->file_name[j] = input_split[i];
			cmd->file_name[j+1] = NULL;
			whats_next = FILES;
			j++;
		}
		else if (ft_strcmp(input_split[i], "<") == 0)
		{
			free(input_split[i]);
			cmd->redir = L_REDIR;
			whats_next = FILES;
		}
		else if (ft_strcmp(input_split[i], "<<") == 0)
		{
			free(input_split[i]);
			cmd->redir = L_HEREDOC;
			whats_next = FILES;
		}
		else if (ft_strcmp(input_split[i], ">") == 0)
		{
			free(input_split[i]);
			cmd->redir = R_REDIR;
			whats_next = FILES;
		}
		else if (ft_strcmp(input_split[i], ">>") == 0)
		{
			free(input_split[i]);
			cmd->redir = R_HEREDOC;
			whats_next = FILES;
		}
		i++;
	}
	return (save);
}
