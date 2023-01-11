#include "../../inc/minishell.h"

int	ft_is_builtins(char *input, t_cmds *cmd, char ** env_cp)
{
	if (!ft_strncmp(input, "export", 6))
	{
		return (0);
	}
	if (!ft_strncmp(input, "cd", 2))
	{
		return (1);
	}
	if (!ft_strncmp(input, "echo", 4))
	{
		return (2);
	}
	if (!ft_strncmp(input, "exit", 4))
	{
		ft_free_split(env_cp);
		ft_exit(cmd->file_name, cmd->args, cmd);
	}
	if (!ft_strncmp(input, "env", 3))
		return (3);
	if (!ft_strncmp(input, "unset", 5))
		return (4);
	if (!ft_strncmp(input, "pwd", 3))
		return (5);
	return (-1);
}

void	ft_dup(t_cmds *cmd, int i)
{
	int		fd[2];
	t_cmds	*next;

	next = cmd->next;
	if (cmd->redir_in == PIPE && i != 0)
	{
		ft_putendl_fd("\nPIPE\n\n", 2);
		dup2(cmd->pipe[0], STDIN_FILENO);
	}
	else if (cmd->infile != NULL && cmd->redir_in == L_REDIR)
	{
		ft_putendl_fd("\nINFILE\n\n", 2);
		fd[0] = open(cmd->infile, O_RDONLY);
		dup2(fd[0], STDIN_FILENO);
	}
	if (cmd->redir_out == PIPE && next)
	{
		ft_putendl_fd("\nNEXT\n\n", 2);
		dup2(next->pipe[1], STDOUT_FILENO);
	}
	if (cmd->outfile[0] != '\0')
	{
		ft_putendl_fd("\nOUTFILE\n\n", 2);
		fd[1] = open(cmd->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
		dup2(fd[1], STDOUT_FILENO);
	}
}

void	ft_make_pipe(t_cmds *cmd)
{
	t_cmds	*next;

	next = cmd->next;
	if (cmd->redir_in != PIPE)
		close(cmd->pipe[0]);
	close(cmd->pipe[1]);
	if (next != NULL)
		pipe(next->pipe);
}

void	ft_close(t_cmds *cmd)
{
	if (cmd->pipe[0] != -1)
		close(cmd->pipe[0]);
	if (cmd->pipe[1] != -1)
		close(cmd->pipe[1]);
}
