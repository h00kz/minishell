#include "../../inc/minishell.h"

static t_envp *get_prev(t_envp *head, t_envp *to_find)
{
    t_envp *cur;

    cur = head;
    if (head == to_find)
        return (NULL);
    while (cur->next)
    {
        if (cur->next == to_find)
            return (cur);
        cur = cur->next;
    }
    return (NULL);
}


static void print_env(t_envp *envp)
{
    t_envp  *head;
    t_envp  *prev;
    t_envp  *tmp;
    t_envp  *a;
    t_envp  *b;

    head = envp;
    while (envp->next)
    {
        a = envp;
        b = envp->next;
        prev = get_prev(head, a);
        if (ft_strcmp(a->variable, b->variable) > 0)
        {
            a->next = b->next;
            b->next = a;
            if (prev)
                prev->next = b;
            else
                continue;
            envp = head;
        }
        envp = envp->next;
    }
    while (head)
    {
        ft_putstr_fd("declare -x ", 1);
        printf("%s=\"%s\"\n", head->variable, head->value);
        head = head->next;
    }
}

int ft_export(char *argv, t_cmds *cmds)
{
    if (!argv)
    {
        print_env(cmds->lst_envp);
    }
    return (0);
}