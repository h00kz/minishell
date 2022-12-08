/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:20:37 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/12/08 14:20:18 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_envp
{
	char			*variable;
	char			*value;
	struct s_envp	*next;
}			t_envp;

typedef struct s_cmds
{
	int				fd_file;
	int				redir_in;
	int				redir_out;
	char			*cmd;
	char			*args;
	char			*infile;
	char			**file_name;
	char			*outfile;
	char			**envp;
	struct s_envp	*lst_envp;
	struct s_cmds	*next;
}			t_cmds;


#endif
