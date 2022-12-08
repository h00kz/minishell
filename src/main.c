/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:53:04 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/12/08 10:33:55 by pdubacqu         ###   ########.fr       */
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

static void	ft_print_lst_e(t_envp *envp)
{
	while (envp != NULL)
	{
		printf("\ncmd->envp->variable = %s", envp->variable);
		printf("\ncmd->envp->value = %s\n", envp->value);
		envp = envp->next;
	}
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
		printf("\ncmd->outfile = %s", cmd->outfile);
		int i = 0;
		while (cmd->file_name[i])
		{
			printf("\ncmd->files = %s", cmd->file_name[i]);
			i++;
		}
		ft_print_lst_e(cmd->lst_envp);
		printf ("\n");
		cmd = tmp;
	}
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n"); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
		rl_replace_line("", 0); // Clear the previous text
		return ;
	}
}

int main(int ac, char **av, char **envp)
{
	char	*input;
	t_cmds	*cmd;
	char	*prompt;

	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_putendl_fd("SIGNAL INTR CTRL C ERROR DEBILE", 2); //wrEFUHWEIUFHRIUGHETHGSRT
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		ft_putendl_fd("SIGNAL QUIT CTRL \\ ERROR DEBILE", 2); // UIWHEFIWUEFHIWUHEF
	if (ac != 1)
		exit(1);
	while (1)
	{
		prompt = set_prompt(envp);
		input = readline(prompt);
		add_history(input);
		free(prompt);
		if (input == NULL || !ft_strncmp(input, "exit", 4))
		{
			printf("exit\n");
			rl_clear_history();
			free(input);
			exit(0); 
		}
		if (input && input[0])
		{
			cmd = parse_input(input, envp);
			if (cmd != NULL)
			{
				ft_print_lst(cmd);
				free_cmd(cmd);
			}
			free(input);	
		}
	}
	return 0;
}
