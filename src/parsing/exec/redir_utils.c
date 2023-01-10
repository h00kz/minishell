#include "../../../inc/minishell.h"

int	ft_strlen_sep(char *str)
{
	int	i;
	int	j;
	int	boolean;

	i = 0;
	j = 0;
	boolean = 0;
	while (str[i])
	{
		if (str[i] == '\"' && boolean == 0)
			boolean = 1;
		else if (str[i] == '\'' && boolean == 0)
			boolean = 2;
		else if (str[i] == '\'' && boolean == 2)
			boolean = 0;
		else if (str[i] == '\"' && boolean == 1)
			boolean = 0;
		if ((boolean == 0 || boolean == 2)
			&& (str[i] == '<' || str[i] == '>' || str[i] == '|'))
			j += 2;
		i++;
		j++;
	}
	return (j);
}

int	ft_check_bool(char *str, int i, int boolean)
{
	if (str[i] == '\"' && boolean == 0)
		boolean = 1;
	else if (str[i] == '\'' && boolean == 0)
		boolean = 2;
	else if (str[i] == '\'' && boolean == 2)
		boolean = 0;
	else if (str[i] == '\"' && boolean == 1)
		boolean = 0;
	return (boolean);
}

char	*add_space_heredoc(char *str, char *s, int *i, int *j)
{
	s[(*j)] = ' ';
	(*j)++;
	s[(*j)] = str[(*i)];
	(*j)++;
	(*i)++;
	s[(*j)] = str[(*i)];
	(*j)++;
	s[(*j)] = ' ';
	return (s);
}

char	*add_space(char *str, char *s, int i, int *j)
{
	s[(*j)] = ' ';
	(*j)++;
	s[(*j)] = str[i];
	(*j)++;
	s[(*j)] = ' ';
	return (s);
}

int	ft_check_add_space(int j, char *str, int i, int boolean)
{
	if (j == 1)
		return ((boolean == 0 || boolean == 2)
			&& ((str[i] == '<' && str[i + 1] == '<')
				|| (str[i] == '>' && str[i + 1] == '>')));
	else
		return ((boolean == 0 || boolean == 2)
			&& (str[i] == '<' || str[i] == '>' || str[i] == '|'));
}
