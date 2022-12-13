#include "../../inc/minishell.h"

int	ft_check_pipe(char *input)
{
	int	i;

	i = 0;
	while (i < ft_strlen(input))
	{
		if (input && input[i] == '|')
		{
			i++;
			while (input && input[i] && (input[i] == ' ' || input[i] == '\t'))
			{
				i++;
				if (input && input[i] && input[i] == '|')
				{
					printf("\nsyntax error\n");
					return (1);
				}
			}
			if (!(input[i]))
			{
				printf("\nsyntax error\n");
				return (1);
			}
		}
		if (input && input[i] == '<')
		{
			i++;
			while (input && input[i] && (input[i] == ' ' || input[i] == '\t'))
			{
				i++;
				if (input && input[i] && input[i] == '<')
				{
					printf("\nsyntax error\n");
					return (1);
				}
			}
			if (!(input[i]))
			{
				printf("\nsyntax error\n");
				return (1);
			}
		}
		if (input && input[i] == '>')
		{
			i++;
			while (input && input[i] && (input[i] == ' ' || input[i] == '\t'))
			{
				i++;
				if (input && input[i] && input[i] == '>')
				{
					printf("\nsyntax error\n");
					return (1);
				}
			}
			if (!(input[i]))
			{
				printf("\nsyntax error\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	make_left_redir(t_cmds *cmd, char **input_split, int *i)
{
	free(cmd->infile);
	if (input_split[(*i) +1])
	{
		cmd->fd_file = open(input_split[(*i) + 1], O_RDONLY);
		if (cmd->redir_in != L_HEREDOC)
		{
			cmd->infile = ft_strdup(input_split[(*i) + 1]);
			cmd->redir_in = L_REDIR;
		}
		if (cmd->fd_file < 0)
		{
			printf("cannot open file : %s\n", cmd->infile);
			free_cmd(cmd);
			exit(1);
		}
		close(cmd->fd_file);
		(*i) += 2;
	}
}

void	make_right_redir(t_cmds *cmd, char **input_split, int *i)
{
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->redir_in != R_HEREDOC)
	{
		cmd->redir_out = R_REDIR;
		if (input_split[(*i) +1])
		{
			cmd->outfile = ft_strdup(input_split[*i + 1]);
			cmd->fd_file = open(input_split[*i + 1],
					O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (cmd->fd_file < 0)
			{
				printf("cannot open file : %s\n", cmd->infile);
				free_cmd(cmd);
				exit(1);
			}
			close(cmd->fd_file);
			(*i) += 2;
		}
	}
}

void	make_right_heredoc(t_cmds *cmd, char **input_split, int *i)
{
	cmd->redir_out = R_HEREDOC;
	if (input_split[(*i) +1])
	{
		cmd->infile = ft_strdup(input_split[*i + 1]);
		cmd->fd_file = open(input_split[*i + 1],
				O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (cmd->fd_file < 0)
		{
			printf("cannot open file : %s\n", cmd->outfile);
			free_cmd(cmd);
			exit(1);
		}
		close(cmd->fd_file);
	}
	(*i) += 2;
}

void	make_left_heredoc(t_cmds *cmd, char **input_split, int *i)
{
	cmd->redir_out = L_HEREDOC;
	if (input_split[(*i) +1])
		cmd->infile = ft_strdup(input_split[(*i) + 1]);
	(*i) += 2;
}

void	make_args(t_cmds *cmd, char **input_split, int *i)
{
	char	*tmp;

	if (ft_strcmp(cmd->cmd, "echo") == 0)
	{
		if (ft_check_echo(input_split[(*i)]) == 1)
			exit(1);
	}
	tmp = ft_strjoin(cmd->args, " ");
	free(cmd->args);
	cmd->args = ft_strjoin_free(tmp, input_split[(*i)]);
	(*i)++;
}

void	make_cmd(t_cmds *cmd, char **input_split, int *i)
{
	free(cmd->cmd);
	cmd->cmd = ft_strdup(input_split[(*i)]);
	(*i)++;
}

void	make_file(t_cmds *cmd, char **input_split, int *i, int *n)
{
	cmd->file_name[(*n)] = ft_strdup(input_split[(*i)]);
	(*i)++;
	(*n)++;
}

void	*make_left_redir_implicit(t_cmds *cmd, char **input_split, int *i)
{
	char	*str;

	str = ft_strtrim(input_split[(*i)], "<");
	free(cmd->infile);
	cmd->fd_file = open(str, O_RDONLY);
	if (cmd->redir_in != L_HEREDOC)
	{
		cmd->infile = ft_strdup(str);
		cmd->redir_in = L_REDIR;
	}
	if (cmd->fd_file < 0)
	{
		printf("cannot open file : %s\n", cmd->infile);
		free_cmd(cmd);
		exit(1);
	}
	close(cmd->fd_file);
	(*i)++;
	free(str);
}

void	make_right_redir_implicit(t_cmds *cmd, char **input_split, int *i)
{
	char	*str;

	str = ft_strtrim(input_split[(*i)], ">");
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->redir_in != R_HEREDOC)
	{
		cmd->redir_out = R_REDIR;
		cmd->outfile = ft_strdup(str);
		cmd->fd_file = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (cmd->fd_file < 0)
		{
			printf("cannot open file : %s\n", cmd->outfile);
			free_cmd(cmd);
			exit(1);
		}
		close(cmd->fd_file);
	}
	(*i)++;
	free(str);
}

void	make_right_here_doc_implicit(t_cmds *cmd, char **input_split, int *i)
{
	char	*str;

	str = ft_strtrim(input_split[(*i)], ">>");
	cmd->redir_out = R_HEREDOC;
	cmd->infile = ft_strdup(str);
	cmd->fd_file = open(str, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (cmd->fd_file < 0)
	{
		printf("cannot open file : %s\n", cmd->outfile);
		free_cmd(cmd);
		exit(1);
	}
	close(cmd->fd_file);
	(*i)++;
}

void	make_left_here_doc_implicit(t_cmds *cmd, char **input_split, int *i)
{
	char	*str;

	str = ft_strtrim(input_split[(*i)], "<");
	cmd->redir_out = L_HEREDOC;
	cmd->infile = ft_strdup(str);
	(*i)++;
}

void	make_args_next(t_cmds *cmd, char **input_split, int *i, int *n)
{
	if (input_split[*i] && ft_strncmp(input_split[(*i)], ">>", 2) == 0)
		make_right_here_doc_implicit(cmd, input_split, i);
	else if (input_split[*i] && ft_strcmp(input_split[(*i)], "<<") == 0)
		make_left_heredoc(cmd, input_split, i);
	else if (input_split[*i] && ft_strncmp(input_split[(*i)], "<<", 2) == 0)
		make_left_here_doc_implicit(cmd, input_split, i);
	else if (input_split[*i] && ft_strncmp(input_split[(*i)], "-", 1) == 0)
		make_args(cmd, input_split, i);
	else if (input_split[*i] && cmd->cmd[0] == '\0')
		make_cmd(cmd, input_split, i);
	else if (input_split[*i])
		make_file(cmd, input_split, i, n);
	else if (!(input_split[*i]))
		(*i)++;
}

t_cmds	*make_arg(char **input_split, char **envp, int j)
{
	t_cmds	*cmd;
	int		i;
	int		n;

	i = 0;
	n = 0;
	cmd = ft_lstnew_node(envp);
	while (i < j)
	{
		if (input_split[i] && ft_strcmp(input_split[i], "<") == 0)
			make_left_redir(cmd, input_split, &i);
		else if (input_split[i] && ft_strncmp(input_split[i], "<", 1) == 0)
			make_left_redir_implicit(cmd, input_split, &i);
		else if (input_split[i] && ft_strcmp(input_split[i], ">") == 0)
			make_right_redir(cmd, input_split, &i);
		else if (input_split[i] && ft_strncmp(input_split[i], ">", 1) == 0)
			make_right_redir_implicit(cmd, input_split, &i);
		else if (input_split[i] && ft_strcmp(input_split[i], ">>") == 0)
			make_right_heredoc(cmd, input_split, &i);
		else
			make_args_next(cmd, input_split, &i, &n);
	}
	return (cmd);
}

char	**vars(char **envp, char **input_split)
{
	int		i;
	char	**tmp;
	int		j;

	i = 0;
	j = 0;
	while (input_split[j])
		j++;
	tmp = malloc(sizeof(char *) * (j + 1));
	while (input_split[i])
	{
		tmp[i] = translate_env_vars(input_split[i], envp);
		free(input_split[i]);
		i++;
	}
	tmp[i] = NULL;
	free(input_split);
	return (tmp);
}

t_cmds	*parse_input(char *input, char **envp)
{
	char	**input_split;
	char	**cmd_split;
	t_cmds	*save;
	t_cmds	*cmd;
	int		i;
	int		j;

	i = 0;
	if (ft_check_pipe(input) == 1)
		return (NULL);
	if (input == NULL)
		return (NULL);
	// ft_make_here_doc(input);
	cmd_split = ft_split_input(input, '|');
	while (cmd_split && cmd_split[i])
	{
		j = 0;
		input_split = ft_split_input(cmd_split[i], ' ');
		while (input_split[j])
			j++;
		input_split = vars(envp, input_split);
		if (input_split == NULL)
		{
			printf("Error idx = %d\n", i);
			ft_nfree_split(input_split, j);
			return (NULL);
		}
		if (i == 0)
			cmd = make_arg(input_split, envp, j);
		else
			ft_lstadd_back_cmd(&cmd, make_arg(input_split, envp, j));
		ft_nfree_split(input_split, j);
		i++;
	}
	if (cmd->cmd == NULL)
	{
		printf("Error\n");
		return (cmd);
	}
	ft_free_split(cmd_split);
	return (cmd);
}
