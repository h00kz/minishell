/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:38:35 by pdubacqu          #+#    #+#             */
/*   Updated: 2022/12/05 14:07:31 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "structs.h"
# include "lists.h"

enum	e_redir
{
	L_REDIR = 1,
	R_REDIR = 2,
	L_HEREDOC = 3,
	R_HEREDOC = 4,
	PIPE = 5,
};
	
enum	e_parsing
{
	FILES = 0,
	INFILE = 1,
	CMD = 2,
	ARGS_OR_FILE = 3,
	FILES_OR_CMD = 4,
};

/********************************parsing************************************/

t_cmds	*ft_make_first_arg(char **input_split, char **envp);
t_cmds	*parse_input(char *input, char **envp);

/*********************************utils*************************************/

t_cmds	*ft_lstnew_node(void);
t_cmds	*lstnew_cmd(char **input_split, char **envp);
char	**ft_split_input(char const *s, char c);
void	free_cmd(t_cmds *cmd);

#endif
