/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/16 15:05:39 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_builtin(t_data *info)
{
	t_list	*exlst;

	exlst = info->export_lst;
	while (exlst)
	{
		printf("declare -x ");
		printf("%s=\"%s\"\n", exlst->key, exlst->value);
		exlst = exlst->next;
	}
	exit(0);
}

int	err_export(t_data *info, char **s, t_list *tlst)
{
	two_pointer_free(s);
	ft_lstclear(&tlst);
	err_message(info, "minishell: export: ` ': not a valid identifier");
	return (1);
}

int	export_syntax(t_data *info)
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
		if (char_c(s[i], '='))
			if (find_i(s[i], '=') == 0)
				return (err_export(info, s, tlst));
	i = -1;
	while (s[++i])
		change_export(info, s[i]);
	two_pointer_free(s);
	ft_lstclear(&tlst);
	return (0);
}

void	env_builtin(t_data *info)
{
	t_list	*envlst;

	envlst = info->env_lst;
	while (envlst)
	{
		printf("%s=%s\n", envlst->key, envlst->value);
		envlst = envlst->next;
	}
	exit(0);
}

int	add_export(t_data *info, char *rl)
{
	t_list	*tmp;

	tmp = info->env_lst;
	if (!check_builtin_str(info, "export") && info->cmd->commands[1])
	{
		if (export_syntax(info))
			g_data->exit_code = 1;
		else
			g_data->exit_code = 0;
		free_info_and_rl(info, rl);
		return (1);
	}
	return (0);
}
