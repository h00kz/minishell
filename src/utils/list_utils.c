
#include "../../inc/minishell.h"

t_cmds	*ft_lstnew_node(void)
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
	new_node->file_name = ft_calloc(sizeof(char *), 10);
	new_node->outfile = ft_calloc(sizeof(char *), 10);
	return (new_node);
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
	int		i;
	t_cmds	*tmp;

	while (cmd != NULL)
	{
		tmp = cmd;
		cmd = cmd->next;
		i = 0;
		if (tmp->args)
			free(tmp->args);
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free(tmp->outfile);
		ft_free_split(tmp->file_name);
		free(tmp);
	}
}
