/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/10 01:01:55 by mucakmak         ###   ########.fr       */
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

void	change_export(t_data *info, char *s)
{
	char	*tmp;
	char	*tmp2;

	if (ft_char_count(s, '='))
	{
		tmp = ft_substr(s, 0, find_i(s, '='));
		tmp2 = ft_substr(s, find_i(s, '=') + 1, 
			ft_strlen(s) - find_i(s, '=') + 1);
		export_control_and_change(info, tmp, tmp2);
	}
	else
		export_control_and_change(info, s, ft_strdup(""));
}

int	export_syntax(t_data *info)
{
	int		i;
	t_list	*tlst;
	char **s;

	i = 0;
	tlst = NULL;
	while (info->cmd->commands[++i])
		ft_lstadd_back(&tlst, ft_lstnew((void *)(long)info->cmd->flags[i], info->cmd->commands[i]));
	s = lst_redirect_combining(tlst);
	i = -1;
	while (s[++i])
		if (ft_char_count(s[i], '='))
			if (find_i(s[i], '=') == 0)
				return (err_message("Syntax Error"));
	i = -1;
	while (s[++i])
		change_export(info, s[i]);
	return (0);
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
	ft_lstadd_back(&info->env_lst, ft_lstnew(s, p));
	return (1);
}

int    add_export(t_data *info, char *rl)
{
	char	**s;
	t_list	*tmp;

	tmp = info->env_lst;
    if (!check_builtin_str(info, "export\0") && info->cmd->commands[1])
	{
		export_syntax(info);
        free_info_and_rl(info, rl);
		ft_lstclear(&info->arg);
    	return (1);
	}
    return (0);
}
