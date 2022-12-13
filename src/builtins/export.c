#include "../../inc/minishell.h"

static void ft_swap(char **a, char **b)
{
    char    *tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

static void print_env(t_envp *envp)
{
    t_envp  *a;
    t_envp  *b;

    a = envp;
    b = envp;
    while (a)
    {
        b = a->next;
        while (b)
        {
            if (ft_strcmp(a->variable, b->variable) > 0)    
            {
                ft_swap(&a->variable, &b->variable);
                ft_swap(&a->value, &b->value);
            }
            b = b->next;
        }
        a = a->next;
    }
    while (envp)
    {
        ft_putstr_fd("declare -x ", 1);
        printf("%s=\"%s\"\n", envp->variable, envp->value);
        envp = envp->next;
    }
}

int ft_export(char *argv, t_cmds *cmds)
{
    // update_cmds_env(cmds);
    if (!argv)
    {
        print_env(cmds->lst_envp);
    }
    return (0);
}