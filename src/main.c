/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:53:04 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/12/05 17:01:04 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*set_prompt(char **envp)
{
	int		i;
	char	*prompt;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PWD=", (long unsigned int)4) == 0)
			break ;
		i++;
	}
	prompt = ft_strjoin(envp[i] + 8, "/:> ");
	return (prompt);
}

void	ft_print_lst(t_cmds *cmd)
{
	t_cmds	*tmp;

	while (cmd != NULL)
	{
		printf ("\n");
		tmp = cmd->next;
		printf("\ncmd->cmd = %s", cmd->cmd);
		printf("\ncmd->args = %s", cmd->args);
		printf("\ncmd->redir_in = %d", cmd->redir_in);
		printf("\ncmd->redir_out = %d", cmd->redir_out);
		printf("\ncmd->infile = %s", cmd->infile);
		printf("\ncmd->outfile = %s", cmd->outfile[0]);
		int i = 0;
		while (cmd->file_name[i])
		{
			printf("\ncmd->files = %s", cmd->file_name[i]);
			i++;
		}
		printf ("\n");
		cmd = tmp;
	}
}

int main(int ac, char **av, char **envp)
{
	char	*input;
	t_cmds	*cmd;
	char	*prompt;

	if (ac != 1)
		exit(1);
	while (1)
	{
		prompt = set_prompt(envp);
		input = readline(prompt);
		add_history(input);
		free(prompt);
		if (input == NULL)
			exit(0);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			clear_history();
			exit(0);
		}
		if (input && input[0])
			cmd = parse_input(input, envp);
		if (input && input[0])
			ft_print_lst(cmd);
		if (input && input[0])
			free_cmd(cmd);
		free(input);
	}
	return 0;
}
