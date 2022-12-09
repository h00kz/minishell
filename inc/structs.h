
#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_cmds
{
	int				fd_file;
	int				redir_in;
	int				redir_out;
	char			*cmd;
	char			*args;
	char			*infile;
	char			**file_name;
	char			*outfile;
	char			**envp;
	struct s_cmds	*next;
}			t_cmds;

#endif
