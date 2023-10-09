/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/09 16:43:42 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_split(t_data *info, t_list **lst, char *s, int in)
{
	int	i;
	int tmp;
	t_list	*temp;

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
	char **str;

	str = info->cmd->commands;
	while (str[i])
	{
		if (ft_char_count(str[i], '|') > 0 && (void *)(long)info->cmd->flags[i] == Q0)
			break ;
		if ((void *)(long)info->cmd->flags[i] == Q0 && (ft_char_count(str[i], '>') 
			|| ft_char_count(str[i], '<')))
			redirect_split(info, lst, str[i], i);
		else
			ft_lstadd_back(lst, ft_lstnew((void *)(long)info->cmd->flags[i], str[i]));
		i++;
	}
}

t_list	*go_redirect(t_list *lst)
{
	while (lst)
	{
		if (lst->key == Q0 && (ft_char_count(lst->value, 
			'>') || ft_char_count(lst->value, '<')))
				return (lst);
		lst = lst->next;
	}
	return (lst);
}

char	*rd_last_str(t_list	*lst)
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


void	overwrite_output(t_data *info, t_list	*lst)
{
	int		fd;
	char	*s;

	s = rd_last_str(lst);
	fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
 	dup2(fd, 1);
	close(fd);
	return ;
}

void	append_output(t_data *info, t_list	*lst)
{
	int		fd;
	char	*s;

	s = rd_last_str(lst);
	fd = open(s, O_WRONLY | O_CREAT | O_APPEND, 0644);
 	dup2(fd, 1);
	close(fd);
	return ;
}

void	overwrite_input(t_data *info, t_list	*lst)
{
	int		fd;
	char	*s;

	s = rd_last_str(lst);
	fd = open(s, O_RDONLY, 0644);
 	dup2(fd, 0);
	close(fd);
	return ;
}


void	append_input(t_data *info, t_list	*lst)
{
	char	*s;
	char	*rd;
	static int counter = 0;

	pipe(info->process->fd);
	counter++;
	s = rd_last_str(lst);
	while (1)
	{
		rd = readline("> ");
		if (!ft_strcmp(rd, s))
			break;
		ft_putstr_fd(rd, info->process->fd[1]);
		ft_putchar_fd('\n', info->process->fd[1]);
	}
	// write(1, "sdf", 1);
	pipe_close(info);
	return ;
}

void	lst_run_redirect(t_data *info, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		tmp = go_redirect(tmp);
		if (tmp && tmp->next && ft_char_count(tmp->value, '>') == 1)
			overwrite_output(info, tmp);
		else if (tmp && tmp->next && ft_char_count(tmp->value, '>') == 2)
			append_output(info, tmp);
		else if (tmp && tmp->next && ft_char_count(tmp->value, '<') == 1)
			overwrite_input(info, tmp);
		else if (tmp && tmp->next && ft_char_count(tmp->value, '<') == 2)
			append_input(info, tmp);
		if (tmp)
			tmp = tmp->next;
	}
}

char	**redirect(t_data *info, int count)
{
	int	j;
	t_list *lst;
	char	**str;

	lst = NULL;

	lst_add_redirect(info, &lst, count);
	lst_run_redirect(info, &lst);

	str = lst_redirect_combining(lst);
	return (str);
}
 