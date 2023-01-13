/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:26:04 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/01/13 11:26:05 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	ft_left_redir(char **input_split, int *i)
{
	int	output;

	output = open(input_split[(*i) + 1], O_RDONLY);
	if (output != -1)
		close (output);
	else
		return (1);
	(*i)++;
	return (0);
}

char	*ft_str_add_space(char *str)
{
	int		i;
	int		j;
	char	*s;
	int		boolean;

	boolean = 0;
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	s = ft_calloc(sizeof(char), ft_strlen_sep(str) + 2);
	while (str[i])
	{
		boolean = ft_check_bool(str, i, boolean);
		if (ft_check_add_space(1, str, i, boolean))
			s = add_space_heredoc(str, s, &i, &j);
		else if (ft_check_add_space(0, str, i, boolean))
			s = add_space(str, s, i, &j);
		else
			s[j] = str[i];
		j++;
		i++;
	}
	s[ft_strlen_sep(str) + 1] = '\0';
	return (s);
}

int	make_left_redir(t_cmds *cmd, char **input_split, int *i)
{
	if (input_split[(*i) + 1])
	{
		cmd->fd_file = open(input_split[(*i) + 1], O_RDONLY);
		free(cmd->infile);
		cmd->infile = ft_strdup(input_split[(*i) + 1]);
		cmd->redir_in = L_REDIR;
		if (cmd->fd_file < 0)
		{
			printf("cannot open file %s\n", cmd->infile);
			return (1);
		}
		close(cmd->fd_file);
		(*i) += 2;
	}
	return (0);
}

int	make_right_redir(t_cmds *cmd, char **input_split, int *i)
{
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->redir_out = R_REDIR;
	if (input_split[(*i) + 1])
	{
		cmd->outfile = ft_strdup(input_split[*i + 1]);
		cmd->fd_file = open(input_split[*i + 1],
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (cmd->fd_file < 0)
		{
			printf("cannot open file : %s\n", cmd->outfile);
			return (1);
		}
		close(cmd->fd_file);
		(*i) += 2;
	}
	return (0);
}

void	ft_increment(int *i, int *n)
{
	(*n)++;
	(*i)++;
}
