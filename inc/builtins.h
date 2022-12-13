#ifndef BUILTINS_H
# define BUILTINS_H

/*********************************** ECHO *************************************/
int		ft_echo(char **argv, char *opt, t_cmds *cmds);

/*********************************** CD *************************************/
int		ft_cd(char *argv, char *opt, t_cmds *cmds);

/*********************************** EXPORT *************************************/
int		ft_export(char **argv, char *opt, t_cmds *cmds);

#endif