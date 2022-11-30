/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:53:04 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/11/30 16:15:29 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	set_prompt(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PWD=", (long unsigned int)4) == 0)
			break ;
		i++;
	}
	printf("%s > ", envp[i] + 8);
}

int main(int ac, char **av, char **envp)
{
	char	*input;
	t_envp	*envp_lst;

	// if (ac != 1)
		// exit(1);
	envp_lst = save_envp(envp);
	lst_print(envp_lst);
	// while (1)
	// {
	// 	set_prompt(envp);
	// 	input = readline(NULL);
	// 	// parse_input(input, envp);
		
	// }
	return 0;
}
