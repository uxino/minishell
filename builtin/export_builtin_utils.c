/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:09:37 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/12 13:24:07 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_is_path(t_data *info, char *s, char *p)
{
	if (!ft_strcmp(s, "PATH"))
	{
		two_pointer_free(info->paths);
		info->paths = ft_split(p, ':');
	}
}

int	check_valid(char *s, int i)
{
	if (ft_char_count(s, ' '))
	{
		printf("minishell: ' ' is not a valid identifier\n");
		if (i)
			free(s);
		return (1);
	}
	if (ft_char_count(s, '?'))
	{
		printf("minishell: '?' is not a valid identifier\n");
		if (i)
			free(s);
		return (1);
	}
	return (0);
}

void	change_export(t_data *info, char *s)
{
	char	*tmp;
	char	*tmp2;

	if (ft_char_count(s, '='))
	{
		tmp = ft_substr(s, 0, find_i(s, '='));
		if (check_valid(tmp, 1))
			return ;
		tmp2 = ft_substr(s, find_i(s, '=') + 1, ft_strlen(s)
				- find_i(s, '=') + 1);
		export_control_and_change(info->env_lst, tmp, tmp2, 1);
		tmp = ft_substr(s, 0, find_i(s, '='));
		tmp2 = ft_substr(s, find_i(s, '=') + 1, ft_strlen(s)
				- find_i(s, '=') + 1);
		export_is_path(info, tmp, tmp2);
		export_control_and_change(info->export_lst, tmp, tmp2, 1);
	}
	else
	{
		if (check_valid(s, 0))
			return ;
		if (!find_key_and_get_char(info->export_lst, s))
			export_control_and_change(info->export_lst,
				ft_strdup(s), ft_strdup(""), 0);
	}
}

int	export_control_and_change(t_list *info, char *s, char *p, int i)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = info;
	while (tmp)
	{
		if (!ft_strcmp((const char *)tmp->key, s))
		{
			if (i)
			{
				free(s);
				free(tmp->value);
				tmp->value = p;
			}
			return (0);
		}
		tmp = tmp->next;
	}
	tmp2 = ft_lstnew(s, p);
	ft_lstadd_back(&info, tmp2);
	return (1);
}
