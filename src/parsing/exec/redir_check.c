/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:26:01 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/01/13 13:02:19 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	ft_check_bool_redir(int boolean, int *i, char *input)
{
	if (input[(*i)] == '"' && boolean == 0)
	{
		boolean = 1;
		(*i)++;
	}
	else if (input[(*i)] == '"' && boolean == 1)
	{
		boolean = 0;
		(*i)++;
	}
	else if (input[(*i)] == '\'' && boolean == 0)
	{
		boolean = 2;
		(*i)++;
	}
	else if (input[(*i)] == '\'' && boolean == 2)
	{
		boolean = 0;
		(*i)++;
	}
	return (boolean);
}

int	ft_make_redir_pipe(char *input, int *i)
{
	(*i)++;
	while (input && input[(*i)] && (input[(*i)] == ' ' || input[(*i)] == '\t'))
	{
		(*i)++;
		if (input && input[(*i)] && input[(*i)] == '|')
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (1);
		}
	}
	if (!(input[(*i)]))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	ft_make_redir_left(char *input, int *i)
{

	(*i)++;
	while (input && input[(*i)] && (input[(*i)] == ' ' || input[(*i)] == '\t'))
	{
		(*i)++;
		if (input && input[(*i)] && input[(*i)] == '<')
		{
			printf("minishell: syntax error near unexpected token `<'\n");
			return (1);
		}
	}
	if (!(input[(*i)]))
	{
		printf("minishell: syntax error near unexpected token `<'\n");
		return (1);
	}
	return (0);
}

static int	ft_check_input(int i, char *input)
{
	int j;

	j = i;
	while (j != 0)
	{
		if (ft_isalnum(input[j]) > 0)
			break ;
		j--;
	}
	if (j == 0 && ft_isalnum(input[j]) <=  0)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	ft_check_redir(char *input)
{
	int	i;
	int	boolean;
	int	error;

	boolean = 0;
	i = -1;
	error = 0;
	while (++i < (int)ft_strlen(input))
	{
		boolean = ft_check_bool_redir(boolean, &i, input);
		if (input && input[i] == '|' && boolean != 2 && boolean != 1)
		{
			if (ft_check_input(i, input) == 1)
				return (1);
			error = ft_make_redir_pipe(input, &i);
		}
		else if (input && input[i] == '<' && boolean != 2 && boolean != 1)
			error = ft_make_redir_left(input, &i);
		else if (input && input[i] == '>' && boolean != 2 && boolean != 1)
			error = ft_make_redir_right(input, &i);
		if (error != 0)
			return (error);
	}
	return (0);
}
