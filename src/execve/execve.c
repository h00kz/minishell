#include "../../inc/minishell.h"

int	ft_is_builtins(char *input, t_cmds *cmd, char ** env_cp)
{
	if (!ft_strncmp(input, "export", 6))
		return (0);
	if (!ft_strncmp(input, "cd", 2))
		return (1);
	if (!ft_strncmp(input, "echo", 4))
		return (2);
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

// static void	ft_dup_next(t_cmds *cmd)
// {
// 	if (cmd->index_cmd % 2 == 0)
// 	{
// 		dup2(cmd->pipe2[0], 0);
// 		dup2(cmd->pipe[1], 1);
// 	}
// 	else
// 	{
// 		dup2(cmd->pipe[0], 0);
// 		dup2(cmd->pipe2[1], 1);
// 	}
// }

void	ft_dup(t_cmds *cmd)
{
	int		fd[2];
	t_cmds	*next;

	next = cmd->next;
	if (cmd->redir_in == PIPE)
		dup2(cmd->pipe[0], STDIN_FILENO);
	if (cmd->file_name[0] != NULL)
	{
		fd[0] = open(cmd->file_name[0], O_RDONLY);
		dup2(fd[0], STDIN_FILENO);
	}
	else if (cmd->infile != NULL)
	{
		fd[0] = open(cmd->infile, O_RDONLY, 0644);
		dup2(fd[0], STDIN_FILENO);
	}
	if (cmd->outfile[0] != '\0')
	{
		fd[1] = open(cmd->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
		dup2(fd[1], STDOUT_FILENO);
	}
	if (cmd->redir_out == PIPE)
	{
		close(cmd->pipe[1]);
		dup2(next->pipe[1], STDOUT_FILENO);
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
	if (cmd->pipe[0] != -1)
		close(cmd->pipe[0]);
	if (cmd->pipe[1] != -1)
		close(cmd->pipe[1]);
}