#include "../../inc/minishell.h"

void	free_cmd(t_cmds *cmd)
{
	t_cmds	*tmp;

	while (cmd != NULL)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->args)
			free(tmp->args);
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free(tmp->outfile);
		if (tmp->heredoc_in)
			free(tmp->heredoc_in);
		if (tmp->heredoc_out)
			free(tmp->heredoc_out);
		ft_free_split(tmp->envp);
		ft_free_split(tmp->file_name);
		ft_lst_free(tmp->lst_envp);
		free(tmp);
	}
}

void	ft_lst_free(t_envp *lst)
{
	t_envp	*current;

	if (!lst)
		return ;
	while (lst)
	{
		current = lst;
		lst = (lst)->next;
		free(current->variable);
		if (current->value)
			free(current->value);
		free(current);
	}
}

t_envp	*lstlast_envp(t_envp *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_lst_size_env(t_envp *lst_envp)
{
	int	i;

	i = 0;
	if (!lst_envp)
		return (i);
	while (lst_envp)
	{
		i++;
		lst_envp = lst_envp->next;
	}
	return (i);
}

void	update_cmds_env(t_cmds *cmds)
{
	if (!cmds)
		return ;
	while (cmds)
	{
		if (cmds->envp)
			ft_free_split(cmds->envp);
		cmds->envp = rebuild_envp(cmds->lst_envp);
		cmds = cmds->next;
	}
}
