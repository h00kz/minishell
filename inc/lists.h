#ifndef LISTS_H
# define LISTS_H

void	ft_lstadd_back_cmd(t_cmds **lst, t_cmds *new);
void	lstadd_back_envp(t_envp **lst, t_envp *new);
t_envp	*save_envp(char **envp);
t_envp	*lstnew_envp(char *variable, char *value);
t_envp	*lstlast_envp(t_envp *lst);
void	ft_lst_free(t_envp *lst);
int		ft_lst_size_env(t_envp *lst_envp);
t_envp	*ch_var_lst_envp(t_envp *lst_envp, char *var, char *value);
char	**rebuild_envp(t_envp *lst_envp);

#endif