#include "../../inc/minishell.h"

int	ft_check_redir(char *input)
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
					printf("syntax error\n");
					return (1);
				}
			}
			if (!(input[i]))
			{
				printf("syntax error\n");
				return (1);
			}
		}
		else if (input && input[i] == '<')
		{
			i++;
			while (input && input[i] && (input[i] == ' ' || input[i] == '\t'))
			{
				i++;
				if (input && input[i] && input[i] == '<')
				{
					printf("syntax error\n");
					return (1);
				}
			}
			if (!(input[i]))
			{
				printf("syntax error\n");
				return (1);
			}
		}
		else if (input && input[i] == '>')
		{
			i++;
			while (input && input[i] && (input[i] == ' ' || input[i] == '\t'))
			{
				i++;
				if (input && input[i] && input[i] == '>')
				{
					printf("syntax error\n");
					return (1);
				}
			}
			if (!(input[i]))
			{
				printf("syntax error\n");
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}

int	ft_strlen_sep(char *str)
{
	int	i;
	int	j;
	int	boolean;

	i = 0;
	j = 0;
	boolean = 0;
	while (str[i])
	{
		if (str[i] == '\"' && boolean == 0)
			boolean = 1;
		else if (str[i] == '\'' && boolean == 0)
			boolean = 2;
		else if (str[i] == '\'' && boolean == 2)
			boolean = 0;
		else if (str[i] == '\"' && boolean == 1)
			boolean == 0;
		if ((boolean == 0 || boolean == 2) && (str[i] == '<' || str[i] == '>' || str[i] == '|'))
			j += 2;
		i++;
		j++;
	}
	return (j);
}

char	*ft_str_add_space(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*s;
	int		boolean;

	boolean = 0;
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	len = ft_strlen_sep(str);
	s = ft_calloc(sizeof(char), len + 2);
	while (str[i])
	{
		if (str[i] == '\"' && boolean == 0)
			boolean = 1;
		else if (str[i] == '\'' && boolean == 0)
			boolean = 2;
		else if (str[i] == '\'' && boolean == 2)
			boolean = 0;
		else if (str[i] == '\"' && boolean == 1)
			boolean == 0;
		if ((boolean == 0 || boolean == 2) && ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>')))
		{
			s[j] = ' ';
			j++;
			s[j] = str[i];
			j++;
			i++;
			s[j] = str[i];
			j++;
			s[j] = ' ';
		}
		else if ((boolean == 0 || boolean == 2) && (str[i] == '<' || str[i] == '>' || str[i] == '|'))
		{
			s[j] = ' ';
			j++;
			s[j] = str[i];
			j++;
			s[j] = ' ';
		}
		else
			s[j] = str[i];
		j++;
		i++;
	}
	s[len + 1] = '\0';
	return (s);
}

int	make_left_redir(t_cmds *cmd, char **input_split, int *i)
{
	if (input_split[(*i) +1])
	{
		cmd->fd_file = open(input_split[(*i) + 1], O_RDONLY);
		free(cmd->infile);
		cmd->infile = ft_strdup(input_split[(*i) + 1]);
		cmd->redir_in = L_REDIR;
		if (cmd->fd_file < 0)
		{
			printf("cannot open file : %s\n", cmd->infile);
			free_cmd(cmd);
			return (1);
		}
		close(cmd->fd_file);
		(*i) += 2;
	}
	return (0);
}

int	make_right_redir(t_cmds *cmd, char **input_split, int *i)
{
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->redir_out = R_REDIR;
	if (input_split[(*i) + 1])
	{
		cmd->outfile = ft_strdup(input_split[*i + 1]);
		cmd->fd_file = open(input_split[*i + 1],
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (cmd->fd_file < 0)
		{
			printf("cannot open file : %s\n", cmd->infile);
			free_cmd(cmd);
			return (1);
		}
		close(cmd->fd_file);
		(*i) += 2;
	}
	return (0);
}

int	make_right_heredoc(t_cmds *cmd, char **input_split, int *i)
{
	cmd->redir_out = R_HEREDOC;
	if (input_split[(*i) +1])
	{
		free(cmd->outfile);
		cmd->outfile = ft_strdup(input_split[*i + 1]);
		cmd->fd_file = open(input_split[*i + 1],
				O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (cmd->fd_file < 0)
		{
			printf("cannot open file : %s\n", cmd->outfile);
			free_cmd(cmd);
			return (1);
		}
		close(cmd->fd_file);
	}
	(*i) += 2;
	return (0);
}

int	make_left_heredoc(t_cmds *cmd, char **input_split, int *i)
{
	cmd->redir_out = L_HEREDOC;
	if (input_split[(*i) +1])
	{
		free(cmd->infile);
		cmd->infile = ft_strdup(input_split[(*i) + 1]);
	}
	(*i) += 2;
	return (0);
}

int	make_args(t_cmds *cmd, char **input_split, int *i, int *n)
{
	char	*tmp;
  
	if ((ft_strncmp(cmd->cmd, "echo", 4) == 0 && cmd->args[0] != '\0') || cmd->file_name[0] != NULL)
	{
		cmd->file_name[(*n)] = input_split[(*i)];
		(*i)++;
		(*n)++;
		return (0);
	}
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0 || ft_strncmp(cmd->cmd, "export", 6) == 0)
	{
		cmd->file_name[(*n)] = input_split[(*i)];
		(*i)++;
		(*n)++;
		return (0);
	}
	tmp = ft_strjoin(cmd->args, " ");
	free(cmd->args);
	cmd->args = ft_strjoin_free(tmp, input_split[(*i)]);
	(*i)++;
	return (0);
}

int	make_cmd(t_cmds *cmd, char **input_split, int *i)
{
	free(cmd->cmd);
	cmd->cmd = ft_strdup(input_split[(*i)]);
	(*i)++;
	return (0);
}

int	make_file(t_cmds *cmd, char **input_split, int *i, int *n)
{
	cmd->file_name[(*n)] = ft_strdup(input_split[(*i)]);
	(*i)++;
	(*n)++;
	return (0);
}

int	make_args_next(t_cmds *cmd, char **input_split, int *i, int *n)
{
	int	error;

	error = 0;
	if (input_split[*i] && ft_strcmp(input_split[(*i)], "<<") == 0)
		error = make_left_heredoc(cmd, input_split, i);
	else if (input_split[*i] && ft_strncmp(input_split[(*i)], "-", 1) == 0 && cmd->cmd[0] != '\0')
		error = make_args(cmd, input_split, i, n);
	else if (input_split[*i] && cmd->cmd[0] == '\0')
		error = make_cmd(cmd, input_split, i);
	else if (input_split[*i])
		error = make_file(cmd, input_split, i, n);
	else
		(*i)++;
	return (error);
}

t_cmds	*make_arg(char **input_split, char **envp, int j)
{
	t_cmds	*cmd;
	int		i;
	int		n;
	int		error;

	i = 0;
	n = 0;
	error = 0;
	cmd = ft_lstnew_node(envp);
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

void	ft_make_here_doc(char *input, char **envp)
{
	int		i;
	char	**input_split;
	int		output;

	i = 0;
	output = 0;
	input_split = ft_split_input(input, ' ');
	input_split = vars(envp, input_split);
	while (input_split && input_split[i])
	{
		if (ft_strncmp(input_split[i], "<<", 2) == 0)
		{
			// ft_create_heredoc_in(input_split[i + 1]);
			i++;
		}
		else if (ft_strncmp(input_split[i], "<", 1) == 0)
		{
			output = open(input_split[i + 1], O_RDONLY);
			if (output != -1)
				close (output);
			i++;
		}
		else if (ft_strncmp(input_split[i], ">>", 2) == 0 && output != -1)
		{
			// ft_create_heredoc_out(input_split[i + 1]);
			i++;
		}
		i++;
	}
	ft_free_split(input_split);
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
	input = ft_str_add_space(input);
	if (ft_check_redir(input) == 1)
	{
		free(input);
		return (NULL);
	}
	if (input == NULL)
	{
		free(input);
		return (NULL);
	}
	ft_make_here_doc(input, envp);
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
			free(input);
			return (NULL);
		}
		if (i == 0)
		{
			cmd = make_arg(input_split, envp, j);
			if (!(cmd))
			{
				ft_free_split(cmd_split);
				ft_nfree_split(input_split, j);
				free(input);
				return (NULL);
			}
		}
		else
			ft_lstadd_back_cmd(&cmd, make_arg(input_split, envp, j));
		ft_nfree_split(input_split, j);
		i++;
	}
	free(input);
	ft_free_split(cmd_split);
	return (cmd);
}
