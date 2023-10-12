/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:06:32 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/12 00:10:14 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	overwrite_output(t_data *info, t_list *lst)
{
	int		fd;
	char	*s;

	(void)info;
	s = rd_last_str(lst);
	fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 1);
	close(fd);
	return ;
}

void	append_output(t_data *info, t_list *lst)
{
	int		fd;
	char	*s;

	(void)info;
	s = rd_last_str(lst);
	fd = open(s, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, 1);
	close(fd);
	return ;
}

void	overwrite_input(t_data *info, t_list *lst)
{
	int		fd;
	char	*s;

	(void)info;
	s = rd_last_str(lst);
	fd = open(s, O_RDONLY, 0644);
	dup2(fd, 0);
	close(fd);
	return ;
}

void	append_input(t_data *info, t_list *lst)
{
	char		*s;
	char		*rd;
	static int	counter;

	counter = 0;
	pipe(info->hd->fd);
	counter++;
	s = rd_last_str(lst);
	signal(SIGINT, hg_signal);
	while (1)
	{
		if (g_data->hd->flag)
			break ;
		rd = readline("> ");
		if (!ft_strcmp(rd, s))
			break ;
		ft_putstr_fd(rd, info->hd->fd[1]);
		ft_putchar_fd('\n', info->hd->fd[1]);
	}
	close(info->hd->fd[1]);
	dup2(info->hd->fd[0], 0);
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
