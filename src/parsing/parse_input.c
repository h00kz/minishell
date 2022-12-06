/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:16:09 by pdubacqu          #+#    #+#             */
/*   Updated: 2022/12/06 18:49:19 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			i++;
			while (input[i] == ' ' || input[i] == '\t')
			{
				i++;
				if (input[i] == '|')
				{
					printf("\nya 2 pipe zebi\n\n");
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}

t_cmds	*make_arg(char **input_split, char **envp)
{
	t_cmds	*cmd;
	int		i;
	int		n;
	
	i = 0;
	n = 0;
	cmd = ft_lstnew_node();
	while (input_split[i] && input_split[i] != "|")
	{
		if (ft_strcmp(input_split[i], "<") == 0)
		{
			free(cmd->infile);
			cmd->fd_file = open(input_split[i + 1], O_RDONLY);
			if (cmd->redir_in != L_HEREDOC)
			{
				cmd->infile = ft_strdup(input_split[i + 1]);
				cmd->redir_in = L_REDIR;
			}
			if (cmd->fd_file < 0)
			{
				printf("cannot open file : %s\n", cmd->infile);
				free_cmd(cmd);
				exit(1);
			}
			close(cmd->fd_file);
			i += 2;
		}
		else if (ft_strcmp(input_split[i], ">") == 0)
		{
			if (cmd->outfile)
				free(cmd->outfile);
			if (cmd->redir_in != R_HEREDOC)
			{
				cmd->redir_out = R_REDIR;
				cmd->outfile = ft_strdup(input_split[i + 1]);
				cmd->fd_file = open(input_split[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
				if (cmd->fd_file < 0)
				{
					printf("cannot open file : %s\n", cmd->infile);
					free_cmd(cmd);
					exit(1);
				}
				close(cmd->fd_file);
			}
			i += 2;
		}
		else if (ft_strcmp(input_split[i], ">>") == 0)
		{
			cmd->redir_out = R_HEREDOC;
			cmd->infile = ft_strdup(input_split[i + 1]);
			cmd->fd_file = open(input_split[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (cmd->fd_file < 0)
			{
				printf("cannot open file : %s\n", cmd->infile);
				free_cmd(cmd);
				exit(1);
			}
			close(cmd->fd_file);
			i += 2;
		}
		else if (ft_strcmp(input_split[i], "<<") == 0)
		{
			cmd->redir_out = L_HEREDOC;
			cmd->infile = ft_strdup(input_split[i + 1]);
			i += 2;
		}
		else if (ft_strncmp(input_split[i], "-", 1) == 0)
		{
			if (ft_strcmp(cmd->cmd, "echo") == 0)
			{
				if (ft_check_echo(input_split[i]) == 1)
					exit(1);
			}
			cmd->args = ft_strjoin_free(cmd->args, input_split[i]);
			i++;
		}
		else if (cmd->cmd[0] == '\0')
		{
			free(cmd->cmd);
			cmd->cmd = ft_strdup(input_split[i]);
			i++;
		}
		else
		{
			cmd->file_name[n] = ft_strdup(input_split[i]);
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
	t_cmds	*save;
	int	i;

	i = 0;
	if (ft_check_pipe(input) == 1)
		exit(1);
	cmd_split = ft_split_input(input, '|');
	while (cmd_split && cmd_split[i])
	{
		input_split = ft_split_input(cmd_split[i], ' ');
		if (i == 0)
			cmd = make_arg(input_split, envp);
		else
			ft_lstadd_back_cmd(&cmd, make_arg(input_split, envp));
		ft_free_split(input_split);
		i++;
	}
	ft_free_split(cmd_split);
	return (cmd);
}
