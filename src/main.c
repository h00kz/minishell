/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:53:04 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/12/02 15:11:59 by pdubacqu         ###   ########.fr       */
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
	printf("\n%s > ", envp[i] + 8);
}

void	ft_print_lst(t_cmds *cmd)
{
	t_cmds *tmp;

	
	while (cmd != NULL)
	{
		tmp = cmd->next;
		printf("\ncmd->cmd = %s", cmd->cmd);
		printf("\ncmd->args = %s", cmd->args);
		printf("\ncmd->redir = %d", cmd->redir);
		int i = 0;
		while (cmd->file_name[i])
		{
			printf("\ncmd->files = %s", cmd->file_name[i]);
			i++;
		}
		cmd = tmp;
	}
}

int main(int ac, char **av, char **envp)
{
	char	*input;
	t_cmds	*cmd;

	if (ac != 1)
		exit(1);
	while (1)
	{
		set_prompt(envp);
		input = readline(NULL);
		if (ft_strncmp(input, "exit", 4) == 0)
			exit(0);
		if (input && input[0] != '\0')
			cmd = parse_input(input, envp);
		ft_print_lst(cmd);
		if (cmd)
			free_cmd(cmd);
	}
	return 0;
}
