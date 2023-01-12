#ifndef BUILTINS_H
# define BUILTINS_H

/************************ ECHO *************************/
int		ft_echo(char **argv, char *opt);

/*************************** CD *******************************/
int		ft_cd(char *argv, char *opt, t_cmds *cmds);

/**************************** EXPORT *****************************/
int		ft_export(char **argv, char *opt, t_cmds *cmds, int fd);
int		ft_check_double_var(t_envp *env, char *arg);
char	*get_first_ascii(t_envp *envp);
int	ft_check_print(t_envp *envp);

/*********************** EXIT ************************/
int		ft_exit(char **argv, char *opt, t_cmds *cmd);

/************************* PWD *****************************/
int		ft_pwd(char *opt);

/******************** UNSET ************************/
t_envp	*ft_unset(char **argv, char *opt, t_cmds *cmd);

/******************** ENV ************************/
int		ft_env(char **argv, char *opt, t_cmds *cmd, int fd);

#endif
