#ifndef BUILTINS_H
# define BUILTINS_H

/************************ ECHO *************************/
int		ft_echo(char **argv, char *opt);

/*************************** CD *******************************/
int		ft_cd(char *argv, char *opt, t_cmds *cmds);

/**************************** EXPORT *****************************/
int		ft_export(char **argv, char *opt, t_cmds *cmds);

/*********************** EXIT ************************/
int		ft_exit(char **argv, char *opt, t_cmds *cmd);

/************************* PWD *****************************/
int		ft_pwd(char *opt);

/******************** UNSET ************************/
int		ft_unset(char **argv, char *opt, t_cmds cmd);

#endif
