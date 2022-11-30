/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:53:04 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/11/30 15:49:40 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	set_prompt(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "USER=", (long unsigned int)5) != 0)
		i++;
	}
	printf("%s >", envp[i] + 5);
}

int main(int ac, char **av, char **envp)
{
	char	*input;

	if (ac != 1)
		return (1);
	while (1)
	{
		set_prompt(envp);
		input = readline();
	}
	return 0;
}
