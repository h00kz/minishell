/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:20:37 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/12/02 15:38:10 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_cmds
{
	int				*fd_file;
	int				redir;
	char			**file_name;
	char			*cmd;
	char			*args;
	char			**envp;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}			t_cmds;

#endif
