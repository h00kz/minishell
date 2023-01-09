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
			printf("syntax error\n");
			return (1);
		}
	}
	if (!(input[(*i)]))
	{
		printf("syntax error\n");
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
			printf("syntax error\n");
			return (1);
		}
	}
	if (!(input[(*i)]))
	{
		printf("syntax error\n");
		return (1);
	}
	return (0);
}

int	ft_make_redir_right(char *input, int *i)
{
	(*i)++;
	while (input && input[(*i)] && (input[(*i)] == ' ' || input[(*i)] == '\t'))
	{
		(*i)++;
		if (input && input[(*i)] && input[(*i)] == '>')
		{
			printf("syntax error\n");
			return (1);
		}
	}
	if (!(input[(*i)]))
	{
		printf("syntax error\n");
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
	i = 0;
	error = 0;
	while (i < (int)ft_strlen(input))
	{
		boolean = ft_check_bool_redir(boolean, &i, input);
		if (input && input[i] == '|' && boolean != 2 && boolean != 1)
			error = ft_make_redir_pipe(input, &i);
		else if (input && input[i] == '<' && boolean != 2 && boolean != 1)
			error = ft_make_redir_left(input, &i);
		else if (input && input[i] == '>' && boolean != 2 && boolean != 1)
			error = ft_make_redir_right(input, &i);
		else
			i++;
		if (error != 0)
			return (error);
	}
	return (0);
}
