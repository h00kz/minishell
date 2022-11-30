/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:16:36 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/11/30 16:16:58 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

// ============ ENVP ===============
t_envp	*save_envp(char **envp);
t_envp	*lstnew_envp(char *variable, char *value);
t_envp	*lstlast_envp(t_envp *lst);
void	lst_print(t_envp *lst);
void	lstadd_back_envp(t_envp **lst, t_envp *new);


#endif