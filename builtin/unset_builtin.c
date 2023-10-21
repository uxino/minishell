/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/16 19:53:53 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_is_path(t_data *info, t_list *path_lst)
{
	if (!ft_strcmp(path_lst->key, "PATH"))
	{
		two_pointer_free(info->paths);
		info->paths = ft_split(" ", ' ');
	}
}

void	unset_clear(t_data *info, t_list **lst, char *s)
{
	t_list	*tmp;
	t_list	*tmp4;

	tmp = (*lst);
	while ((*lst)->next)
	{
		if (!ft_strcmp(tmp->key, s))
		{
			tmp = tmp->next;
			break ;
		}
		else if (!ft_strcmp((*lst)->next->key, s))
		{
			tmp4 = (*lst)->next;
			(*lst)->next = (*lst)->next->next;
			unset_is_path(info, tmp4);
			free(tmp4->key);
			free(tmp4->value);
			free(tmp4);
			break ;
		}
		(*lst) = (*lst)->next;
	}
	(*lst) = tmp;
}

void	unset_run(t_data *info, char *s)
{
	t_data	*tmp;

	tmp = info;
	unset_clear(info, &info->env_lst, s);
	unset_clear(info, &info->export_lst, s);
}

int	unset_syntax(t_data *info)
{
	int		i;
	t_list	*tlst;
	char	**s;

	i = 0;
	tlst = NULL;
	while (info->cmd->commands[++i])
		ft_lstadd_back(&tlst, ft_lstnew((void *)(long)info->cmd->flags[i],
				info->cmd->commands[i]));
	s = lst_redirect_combining(tlst);
	i = -1;
	while (s[++i])
		unset_run(info, s[i]);
	two_pointer_free(s);
	ft_lstclear(&tlst);
	return (0);
}

int	unset_builtin(t_data *info, char *rl)
{
	t_data	*tmp;

	tmp = info;
	if (!check_builtin_str(info, "unset"))
	{
		unset_syntax(info);
		free_info_and_rl(info, rl);
		g_data->exit_code = 0;
		return (1);
	}
	return (0);
}
