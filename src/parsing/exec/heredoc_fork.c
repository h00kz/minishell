#include "../../../inc/minishell.h"

static void	sig_handler_child(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 128 + sig;
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
	exit(g_exit_code);
}

t_cmds	*get_some_shit(t_cmds *cmd, char *input, char **envp, int pid)
{
	free_cmd(cmd);
	cmd = ft_get_heredoc_in(input, envp);
	waitpid(pid, NULL, 0);
	return (cmd);
}
