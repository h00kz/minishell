/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:16:09 by pdubacqu          #+#    #+#             */
/*   Updated: 2022/12/06 14:18:19 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmds	*ft_make_first_arg(char **input_split, char **envp)
{
	t_cmds	*cmd;
	int		i;
	int		j;
	int		n;

	j = 0;
	i = 0;
	n = 0;
	cmd = ft_lstnew_node();
	while (input_split[i] && input_split[i] != "|")
	{
		if (ft_strcmp(input_split[i], "<") == 0)
		{
			free(cmd->infile);
			cmd->infile = input_split[i + 1];
			cmd->redir_in = L_REDIR;
			cmd->fd_file = open(cmd->infile, O_RDONLY);
			close(cmd->fd_file); 
			if (cmd->fd_file < 0)
			{
				printf("cannot open file : %s\n", cmd->infile);
				free_cmd(cmd);
			}
			i += 2;
		}
		else if (ft_strcmp(input_split[i], ">") == 0)
		{
			cmd->outfile[j] = input_split[i + 1];
			cmd->redir_out = R_REDIR;
			i += 2;
			j++;
		}
		else if (ft_strcmp(input_split[i], ">>") == 0)
		{
			cmd->redir_out = R_HEREDOC;
			cmd->infile = input_split[i + 1];
			i += 2;
		}
		else if (ft_strcmp(input_split[i], "<<") == 0)
		{
			cmd->redir_out = L_HEREDOC;
			cmd->infile = input_split[i + 1];
			i += 2;
		}
		else if (ft_strncmp(input_split[i], "-", 1) == 0)
		{
			free(cmd->args);
			cmd->args = input_split[i];
			i++;
		}
		else if (cmd->cmd[0] == '\0')
		{
			free(cmd->cmd);
			cmd->cmd = input_split[i];
			i++;
		}
		else
		{
			cmd->file_name[n] = input_split[i];
			i++;
			n++;
		}

	}
	return (cmd);
}


t_cmds	*parse_input(char *input, char **envp)
{
	char	**cmd_split;
	char	**input_split;
	t_cmds	*cmd;
	int	i;

	i = 0;
	cmd_split = ft_split(input, '|');
	input_split = ft_split_input(cmd_split[0], ' ');
	cmd = lstnew_cmd(input_split, envp);
	free(input_split);
	return (cmd);
}
