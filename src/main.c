#include "../inc/minishell.h"

int	g_exit_code[2] = {0, 0};

void	ft_print_lst_e(t_envp *envp)
{
	while (envp != NULL)
	{
		printf("\nenvp->variable = %s", envp->variable);
		printf("\nenvp->print = %d", envp->print);
		printf("\nenvp->value = %s\n", envp->value);
		envp = envp->next;
	}
}

void	ft_print_lst(t_cmds *cmd)
{
	t_cmds	*tmp;
	while (cmd != NULL)
	{
		tmp = cmd->next;
		printf("cmd->cmd = %s", cmd->cmd);
		printf("\ncmd->args = %s", cmd->args);
		printf("\ncmd->redir_in = %d", cmd->redir_in);
		printf("\ncmd->redir_out = %d", cmd->redir_out);
		printf("\ncmd->infile = %s", cmd->infile);
		printf("\ncmd->outfile = %s", cmd->outfile);
		int i = 0;
		printf("\nheredoc_in = %s", cmd->heredoc_in);
		while (cmd->file_name[i])
		{
			printf("\ncmd->files = %s", cmd->file_name[i]);
			i++;
		}
		// ft_print_lst_e(cmd->lst_envp);
		printf ("\n\n");
		cmd = tmp;
	}
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code[0] = 130;
		g_exit_code[1] = 1;
		return ;
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_cmds	*cmd;
	char	**env_cp;

	(void)**av;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	env_cp = ft_cpy_envp(envp);
	if (ac != 1)
		exit(1);
	while (1)
	{
		input = readline("Minishell > ");
		add_history(input);
		if (input == NULL)
		{
			ft_putendl_fd("exit", 1);
			rl_clear_history();
			ft_free_split(env_cp);
			free(input);
			exit(g_exit_code[0]); 
		}
		if (input && input[0])
		{
			cmd = parse_input(input, env_cp);
			if (cmd != NULL  && g_exit_code[1] == 0)
			{
				printf("jlashd\n\n\n\n");
				pipe(cmd->pipe);
				ft_free_split(env_cp);
				ft_fork_execution(cmd);
				ft_close(cmd);
				env_cp = rebuild_envp(cmd->lst_envp);
			}
			g_exit_code[1] = 0;
			ft_print_lst(cmd);
			free_cmd(cmd);
			free(input);
		}
	}
	return (0);
}
