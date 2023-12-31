/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/16 15:05:39 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_split(t_data *info, t_list **lst, char *s, int in)
{
	int		i;
	int		tmp;

	(void)in;
	(void)info;
	i = 0;
	while (s[i])
	{
		tmp = i;
		while (s[i] && s[i] != '>' && s[i] != '<')
			i++;
		ft_lstadd_back(lst, ft_lstnew((void *)Q0, ft_substr(s, tmp, i - tmp)));
		tmp = i;
		while (s[i] && (s[i] == '>' || s[i] == '<'))
			i++;
		ft_lstadd_back(lst, ft_lstnew((void *)Q0, ft_substr(s, tmp, i - tmp)));
	}
}

void	lst_add_redirect(t_data *info, t_list **lst, int i)
{
	char	**str;

	str = info->cmd->commands;
	while (str[i])
	{
		if (char_c(str[i], '|') > 0
			&& (void *)(long)info->cmd->flags[i] == Q0)
			break ;
		if ((void *)(long)info->cmd->flags[i] == Q0 && (char_c(str[i],
					'>') || char_c(str[i], '<')))
			redirect_split(info, lst, str[i], i);
		else
			ft_lstadd_back(lst, ft_lstnew((void *)(long)info->cmd->flags[i],
					str[i]));
		i++;
	}
}

t_list	*go_redirect(t_list *lst)
{
	while (lst)
	{
		if (lst->key == Q0 && (char_c(lst->value, '>')
				|| char_c(lst->value, '<')))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

char	*rd_last_str(t_list *lst)
{
	char	*s;
	t_list	*red;

	red = lst;
	lst = lst->next;
	if (lst->value[0] == ' ' && lst->key == Q0)
		lst = lst->next;
	if (!lst->value[0])
		lst = lst->next;
	if (lst->key == Q0)
		s = ft_strtrim(lst->value, " ");
	else
		s = ft_strdup(lst->value);
	free(lst->value);
	free(red->value);
	if (lst->key == Q0)
		lst->value = ft_strdup(" ");
	else
		lst->value = ft_strdup("");
	red->value = ft_strdup("");
	return (s);
}

char	**redirect(t_data *info, int count, int i)
{
	t_list	*lst;
	char	**str;

	lst = NULL;
	lst_add_redirect(info, &lst, count);
	lst_run_redirect(info, &lst, i);
	str = lst_redirect_combining(lst);
	return (str);
}
