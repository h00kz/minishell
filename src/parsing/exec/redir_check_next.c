/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check_next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:53:50 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/01/13 13:02:02 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	ft_make_redir_right(char *input, int *i)
{
	(*i)++;
	while (input && input[(*i)] && (input[(*i)] == ' ' || input[(*i)] == '\t'))
	{
		(*i)++;
		if (input && input[(*i)] && input[(*i)] == '>')
		{
			printf("minishell: syntax error near unexpected token `>'\n");
			return (1);
		}
	}
	if (!(input[(*i)]))
	{
		printf("minishell: syntax error near unexpected token `>'\n");
		return (1);
	}
	return (0);
}
