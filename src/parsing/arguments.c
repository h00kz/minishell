#include "../../inc/minishell.h"

int	make_args(t_cmds *cmd, char **input_split, int *i, int *n)
{
	char	*tmp;

	if ((ft_strncmp(cmd->cmd, "echo", 4) == 0 && cmd->args[0] != '\0')
		|| cmd->file_name[0] != NULL)
	{
		cmd->file_name[(*n)] = ft_strdup(input_split[(*i)]);
		ft_increment(i, n);
		return (0);
	}
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
	{
		cmd->file_name[(*n)] = ft_strdup(input_split[(*i)]);
		ft_increment(i, n);
		return (0);
	}
	if (cmd->args[0] != '\0')
		tmp = ft_strjoin(cmd->args, " ");
	else
		tmp = ft_calloc(sizeof(char), 1);
	free(cmd->args);
	cmd->args = ft_strjoin_free(tmp, input_split[(*i)]);
	(*i)++;
	return (0);
}

int	make_args_next(t_cmds *cmd, char **input_split, int *i, int *n)
{
	int	error;

	error = 0;
	if (input_split[*i] && ft_strcmp(input_split[(*i)], "<<") == 0)
		error = make_left_heredoc(cmd, input_split, i);
	else if (input_split[*i] && ft_strncmp(input_split[(*i)], "-", 1) == 0
		&& cmd->cmd[0] != '\0')
		error = make_args(cmd, input_split, i, n);
	else if (input_split[*i] && cmd->cmd[0] == '\0')
		error = make_cmd(cmd, input_split, i);
	else if (input_split[*i])
		error = make_file(cmd, input_split, i, n);
	else
		(*i)++;
	return (error);
}

t_cmds	*make_arg(char **input_split, int j, t_cmds *cmd)
{
	int		i;
	int		n;
	int		error;

	i = 0;
	n = 0;
	error = 0;
	while (i < j)
	{
		if (error != 0)
			return (NULL);
		if (input_split[i] && ft_strcmp(input_split[i], "<") == 0)
			error = make_left_redir(cmd, input_split, &i);
		else if (input_split[i] && ft_strcmp(input_split[i], ">") == 0)
			error = make_right_redir(cmd, input_split, &i);
		else if (input_split[i] && ft_strcmp(input_split[i], ">>") == 0)
			error = make_right_heredoc(cmd, input_split, &i);
		else
			error = make_args_next(cmd, input_split, &i, &n);
	}
	return (cmd);
}

char	**ft_make_input_split(char *input, char **envp)
{
	char	**input_split;

	input_split = ft_split_input(input, ' ');
	input_split = vars(envp, input_split);
	return (input_split);
}
