/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:20:37 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/11/30 16:13:04 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_cmds
{
	int				fd_file;
	int				redir;
	char			*file_name;
	char			*cmd;
	char			*args;
	char			**envp;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}			t_cmds;

typedef struct s_envp
{
	char			*variable;
	char			*value;
	struct s_envp	*next;
}			t_envp;

#endif
