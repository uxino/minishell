/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/09 22:40:54 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    export_builtin(t_data *info)
{
    t_list  *envlst;

    envlst = info->env_lst;
    while (envlst)
    {
        printf("declare -x ");
        printf("%s=\"%s\"\n", envlst->key, envlst->value);
        envlst = envlst->next;
    }
    exit(0);
}

void    env_builtin(t_data *info)
{
    t_list  *envlst;

    envlst = info->env_lst;
    while (envlst)
    {
        printf("%s=%s\n", envlst->key, envlst->value);
        envlst = envlst->next;
    }
    exit(0);
}

int	export_control_and_change(t_data *info, char *s, char *p)
{
	int		i;
	int		j;
	t_list *tmp;

	tmp = info->env_lst;
	while (tmp)
	{
		if (!ft_strcmp((const char *)tmp->key, s))
		{
			free(tmp->value);
			tmp->value = ft_strdup(p);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int    add_export(t_data *info, char *rl)
{
	char **s;
	t_list	*tmp;

	tmp = info->env_lst;
    if (!check_builtin_str(info, "export\0") && info->cmd->commands[1] 
		&& ft_char_count(info->cmd->commands[1], '='))
	{
        s = ft_split(info->cmd->commands[1], '=');
		if (export_control_and_change(info, s[0], s[1]))
			ft_lstadd_back(&info->env_lst, ft_lstnew(s[0], s[1]));
		free(s);
        free_info_and_rl(info, rl);
		ft_lstclear(&info->arg);
    	return (1);
	}
    return (0);
}
