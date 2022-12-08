/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_interpretation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:09:17 by pdubacqu          #+#    #+#             */
/*   Updated: 2022/12/08 14:58:39 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_translate(char **envp, char *input)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	i = 1;
	while (input[i] && ft_isalnum(input[i]))
		i++;
	while (envp[j] && ft_strncmp(envp[j], &input[1], i - 1) != 0)
		j++;
	if (envp[j] && envp[j][i - 1] == '=') 
		str = ft_strdup(&envp[j][i]);
	else
		return (NULL);
	return (str);
}

char	*ft_get_vars(char *input)
{
	char	*str;
	int		i;

	i = 0;
	while (input[i] && input[i] != '\'')
		i++;
	str = ft_strndup(input, i);
	return (str);
}

char	*translate_vars(char *input, int *i, char **envp, int *boolean)
{
	char	*str;

	if ((*boolean) != 2)
		str = ft_translate(envp, &input[(*i)]);
	else if ((*boolean) == 2)
		return (ft_get_vars(&input[(*i)]));
	return (str);
}

char	*translate_env_vars(char *input, char **envp)
{
	char	*str;
	char	*tmp;
	int		boolean;
	int		i;
	int		j;

	i = 0;
	j = 0;
	boolean = 0;
	str = NULL;
	while (input && input[i])
	{
		if (input[i] == '"' && boolean == 0)
		{
			boolean = 1;
			i++;
		}
		else if (input[i] == '"' && boolean == 1)
		{
			boolean = 0;
			i++;
		}
		else if (input[i] == '\'' && boolean == 0)
		{
			boolean = 2;
			i++;
		}
		else if (input[i] == '\'' && boolean == 2)
		{
			boolean = 0;
			i++;
		}
		if (input[i] == '$' && boolean != 2)
		{
			tmp = translate_vars(input, &i, envp, &boolean);
			i++;
			while (input[i] && ft_isalnum(input[i]))
				i++;
			if (!tmp)
				i += 2;
			if (tmp)
			{
				str = ft_strjoin_free(str, tmp);
				free(tmp);
			}
		}
		else if (input[i])
		{
			if (input[i] != '"')
			{
				tmp = ft_calloc(sizeof(char), 2);
				tmp[0] = input[i];
				str = ft_strjoin_free_choice(str, tmp, 3);
			}
			i++;
		}
	}
	return (str);
}
