/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:20:37 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/11/30 15:25:48 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_cmds
{
	int				idx;
	int				fd_file;
	char			*file_name;
	char			*cmd;
	char			*args;
	char			*redir;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}			t_cmds;

typedef struct s_envp
{
	int				idx;
	char			*variable;
	char			*value;
	struct s_envp	*next;
}			t_envp;

#endif
