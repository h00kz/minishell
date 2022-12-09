#include "../../inc/minishell.h"

t_envp	*save_envp(char **envp)
{
	t_envp	*lst;
	int		i;
	int		sep_idx;

	i = 0;
	lst = NULL;
	if (!*envp || !envp)
		return (NULL);
	while (envp[i])
	{
		sep_idx = ft_str_index_chr(envp[i], '=');
		lstadd_back_envp(&lst, lstnew_envp(ft_strndup(envp[i], sep_idx), \
										ft_strdup(&envp[i][sep_idx + 1])));
		i++;
	}
	return (lst);
}

t_envp	*ch_var_lst_envp(t_envp *lst_envp, char *var, char *value)
{
	t_envp	*lst;

	lst = lst_envp;
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (!ft_strcmp(lst->variable, var))
		{
			if (lst->value)
				free(lst->value);
			lst->value = ft_strdup(value);
		}
		lst = lst->next;
	}
	return (lst_envp);
}

char	**rebuild_envp(t_envp *lst_envp)
{
	char	**ret_envp;
	char	*tmp;
	int		lst_size;
	int		i;

	i = 0;
	lst_size = ft_lst_size_env(lst_envp);
	ret_envp = ft_calloc(lst_size + 1, sizeof(char *));
	if (!ret_envp)
		return (NULL);
	while (lst_envp)
	{
		tmp = ft_strjoin(lst_envp->variable, "=");
		ret_envp[i] = ft_strjoin(tmp, lst_envp->value);
		free(tmp);
		lst_envp = lst_envp->next;
		i++;
	}
	return (ret_envp);
}