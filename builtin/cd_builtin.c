/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:55:14 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/12 01:13:51 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_key_and_get_char(t_list *lst, char *s)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, s))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

t_list	*and_get_lst(t_list *lst, char *s)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, s))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

int	set_home(t_data *info)
{
	char	*temp;

	if (!info->cmd->commands[1])
	{
		temp = find_key_and_get_char(info->env_lst, "HOME");
		if (temp && !chdir(temp))
		{
			old_pwd_and_pwd_changer(info->env_lst);
			old_pwd_and_pwd_changer(info->export_lst);
			return (1);
		}
		else
			printf("HOME not set\n");
		return (1);
	}
	return (0);
}

int	cd_builtin_2(t_data *info, char *rl)
{
	char	*s;

	if (set_home(info))
	{
		free_info_and_rl(info, rl);
		g_data->exit_code = 0;
		return (1);
	}
	if (info->cmd->flags[1] == Q0)
		s = ft_strtrim(info->cmd->commands[1], " ");
	else
		s = ft_strdup(info->cmd->commands[1]);
	if (chdir(s))
	{
		g_data->exit_code = 1;
		printf("%s : No such file or directory\n", s);
	}
	else
	{
		old_pwd_and_pwd_changer(info->env_lst);
		old_pwd_and_pwd_changer(info->export_lst);
		g_data->exit_code = 0;
	}
	free(s);
	return (0);
}

int	cd_builtin(t_data *info, char *rl)
{
	if (!check_builtin_str(info, "cd"))
	{
		if (cd_builtin_2(info, rl))
			return (1);
		free_info_and_rl(info, rl);
		return (1);
	}
	return (0);
}
