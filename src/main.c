#include "../inc/minishell.h"

int	g_exit_code = 0;

char	*set_prompt(void)
{
	char	*prompt;
	char	*tmp;
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	tmp = ft_strjoin("\033[0;36m[\033[0;32m", cwd);
	prompt = ft_strjoin(tmp, "\033[0;36m]\033[0m> ");
	free(tmp);
	free(cwd);
	return (prompt);
}

// static void	ft_print_lst_e(t_envp *envp)
// {
// 	while (envp != NULL)
// 	{
// 		printf("\ncmd->envp->variable = %s", envp->variable);
// 		printf("\ncmd->envp->value = %s\n", envp->value);
// 		envp = envp->next;
// 	}
// }

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

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 128 + sig;
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_cmds	*cmd;
	char	*prompt;
	char	**env_cp;

	(void)**av;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	env_cp = ft_cpy_envp(envp);
	if (ac != 1)
		exit(1);
	while (1)
	{
		prompt = set_prompt();
		input = readline(prompt);
		free(prompt);
		add_history(input);
		if (input == NULL)
		{
			ft_putendl_fd("exit", 1);
			rl_clear_history();
			ft_free_split(env_cp);
			free(input);
			exit(g_exit_code); 
		}
		if (input && input[0])
		{
			cmd = parse_input(input, env_cp);
			if (cmd != NULL)
			{
				if (!ft_strncmp(input, "export", 6))
					ft_export(cmd->file_name, cmd->args, cmd);
				if (!ft_strncmp(input, "cd", 2))
					ft_cd(cmd->file_name[0], cmd->args, cmd);
				if (!ft_strncmp(input, "echo", 4))
					ft_echo(cmd->file_name, cmd->args);
				if (!ft_strncmp(input, "exit", 4))
					ft_exit(cmd->file_name, cmd->args, cmd);
				if (!ft_strncmp(input, "env", 3))
					ft_env(cmd->file_name, cmd->args, cmd);
				if (!ft_strncmp(input, "unset", 5))
					cmd->lst_envp = ft_unset(cmd->file_name, cmd->args, cmd);
				if (!ft_strncmp(input, "pwd", 3))
					ft_pwd(cmd->args);
				ft_free_split(env_cp);
				env_cp = rebuild_envp(cmd->lst_envp);
			}
			free(input);
			free_cmd(cmd);
		}
	}
	return (0);
}
