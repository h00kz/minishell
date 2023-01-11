#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_envp
{
	char			*variable;
	char			*value;
	int				print;
	struct s_envp	*next;
}			t_envp;

typedef struct s_cmds
{
	int				fd_file;
	int				redir_in;
	int				redir_out;
	int				pipe[2];
	char			*cmd;
	char			*args;
	char			*infile;
	char			*heredoc_in;
	char			*heredoc_out;
	char			**file_name;
	char			*outfile;
	char			**envp;
	struct s_envp	*lst_envp;
	struct s_cmds	*next;
}			t_cmds;

#endif
