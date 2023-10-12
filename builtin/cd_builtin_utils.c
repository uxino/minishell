/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:10:43 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/12 01:39:29 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_changer(t_list *lst)
{
	char	*s;
	t_list	*tmp;

	tmp = lst;
	s = getcwd(NULL, 0);
	if (tmp && !ft_strcmp(tmp->key, "PWD") && s)
	{
		free(tmp->value);
		tmp->value = ft_strdup(s);
	}
	free(s);
}

void	old_pwd_and_pwd_changer_2(t_list *tmp, t_list *pwd)
{
	while (tmp)
	{
		if (pwd && !ft_strcmp(tmp->key, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(pwd->value);
			break ;
		}
		tmp = tmp->next;
	}
}

void	old_pwd_and_pwd_changer(t_list *lst)
{
	t_list	*tmp;
	t_list	*pwd;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			pwd = tmp;
			break ;
		}
		else
			pwd = 0;
		tmp = tmp->next;
	}
	tmp = lst;
	old_pwd_and_pwd_changer_2(tmp, pwd);
	pwd_changer(pwd);
}
