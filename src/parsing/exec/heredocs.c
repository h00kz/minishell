/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:26:07 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/01/13 11:26:08 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	ft_create_heredoc_in(char *str, int i)
{
	int		fd;
	char	*tmp;
	char	*name;

	name = ft_strjoin_free_choice(".heredoc", ft_itoa(i), 2);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(name);
	tmp = get_next_line(0);
	name = ft_strjoin(str, "\n");
	while ((tmp) && (ft_strncmp(name, tmp, ft_strlen(name))) != 0)
	{
		ft_putstr_fd(tmp, fd);
		free(tmp);
		tmp = get_next_line(0);
	}
	if (tmp)
		free(tmp);
	free(name);
	close(fd);
}

void	ft_create_heredoc_out(char *str, int i)
{
	int		fd;
	char	*tmp;
	char	*name;

	name = ft_strjoin_free_choice(".heredoc", ft_itoa(i), 2);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(name);
	tmp = get_next_line(0);
	name = ft_strjoin(str, "\n");
	while ((ft_strncmp(name, tmp, ft_strlen(name))) != 0)
	{
		ft_putstr_fd(tmp, fd);
		free(tmp);
		tmp = get_next_line(0);
	}
	free(tmp);
	free(name);
	close(fd);
}

int	make_right_heredoc(t_cmds *cmd, char **input_split, int *i)
{
	cmd->redir_out = R_HEREDOC;
	if (input_split[(*i) + 1])
	{
		free(cmd->outfile);
		cmd->outfile = ft_strdup(input_split[*i + 1]);
		cmd->fd_file = open(input_split[*i + 1],
				O_CREAT | O_APPEND | O_WRONLY, 0644);
		close(cmd->fd_file);
		if (cmd->fd_file < 0)
		{
			printf("cannot open file : %s\n", cmd->outfile);
			return (1);
		}
	}
	(*i) += 2;
	return (0);
}

int	make_left_heredoc(t_cmds *cmd, char **input_split, int *i)
{
	cmd->redir_in = L_HEREDOC;
	if (input_split[(*i) + 1])
	{
		free(cmd->infile);
		cmd->infile = ft_strdup(input_split[(*i) + 1]);
	}
	(*i) += 2;
	return (0);
}

void	ft_make_heredoc_in(t_cmds *cmd, char **input_split, int *i)
{
	char	*tmp_in;

	if (cmd->heredoc_in[0] != '\0')
		unlink(cmd->heredoc_in);
	ft_create_heredoc_in(input_split[(*i) + 1], (*i));
	free(cmd->heredoc_in);
	tmp_in = ft_strjoin_free_choice(".heredoc", ft_itoa((*i)), 2);
	cmd->heredoc_in = tmp_in;
	(*i)++;
}
