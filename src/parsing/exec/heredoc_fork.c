#include "../../../inc/minishell.h"

static void	sig_handler_child(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code[0] = 130;
		close(STDIN_FILENO);
	}
}

void	ft_fork(t_cmds *cmd, char *input, char **envp)
{
	free_cmd(cmd);
	signal(SIGINT, sig_handler_child);
	cmd = ft_make_here_doc(input, envp);
	free_cmd(cmd);
	free(input);
	ft_free_split(envp);
	exit(g_exit_code[0]);
}

static void	sig_handler_parent(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code[1] = 1;
		g_exit_code[0] = 130;
	}
}

t_cmds	*get_some_shit(t_cmds *cmd, char *input, char **envp, int pid)
{
	signal(SIGINT, sig_handler_parent);
	free_cmd(cmd);
	cmd = ft_get_heredoc_in(input, envp);
	waitpid(pid, NULL, 0);
	signal(SIGINT, sig_handler);
	return (cmd);
}
