#include "../../inc/minishell.h"

t_cmds	*ft_lstnew_node(char **envp)
{
	t_cmds	*new_node;

	new_node = malloc(sizeof(t_cmds) * 1);
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->redir_in = PIPE;
	new_node->redir_out = PIPE;
	new_node->cmd = ft_calloc(sizeof(char), 1);
	new_node->args = ft_calloc(sizeof(char), 1);
	new_node->infile = ft_calloc(sizeof(char), 1);
	new_node->file_name = ft_calloc(sizeof(char *), 50);
	new_node->outfile = ft_calloc(sizeof(char), 1);
	new_node->lst_envp = save_envp(envp);
	new_node->envp = rebuild_envp(new_node->lst_envp);
	new_node->heredoc_in = ft_calloc(sizeof(char), 1);
	new_node->heredoc_out = ft_calloc(sizeof(char), 1);
	return (new_node);
}

t_envp	*lstnew_envp(char *variable, char *value)
{
	t_envp	*new_node;

	new_node = malloc(sizeof(t_envp) * 1);
	if (!new_node)
		return (NULL);
	new_node->variable = variable;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	lstadd_back_envp(t_envp **lst, t_envp *new)
{
	t_envp	*current;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		current = lstlast_envp(*lst);
		current->next = new;
	}
}

void	ft_lstadd_back_cmd(t_cmds **lst, t_cmds *new)
{
	t_cmds	*current;

	current = *(lst);
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

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
		ft_free_split(tmp->file_name);
		ft_lst_free(tmp->lst_envp);
		ft_free_split(tmp->envp);
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