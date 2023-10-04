/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/04 20:24:39 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_process_merge(t_data *info, int i)
{
	if (i == 0)
		dup2(info->process[0].fd[1], 1);
	else if (i == info->pipe_count)
		dup2(info->process[i - 1].fd[0], 0);
	else
	{
		dup2(info->process[i - 1].fd[0], 0);
		dup2(info->process[i].fd[1], 1);
	}
	pipe_close(info);
}

int	find_pipe_count(t_data *info)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (info->cmd->commands[++i])
		if (ft_strchr(info->cmd->commands[i], '|') && info->cmd->flags[i] == Q0)
			count++;
	return (count);
}

void	pipe_finder(t_data *info, int *count)
{
	while (info->cmd->commands[++(*count)])
		if (ft_strchr(info->cmd->commands[*count], '|')
			&& info->cmd->flags[*count] == Q0 && ++(*count))
			break ;
	if (info->cmd->commands[*count]
		&& info->cmd->commands[*count][0] == ' '
		&& info->cmd->flags[*count] == Q0)
	{
		++(*count);
	}
}

void	pipe_close(t_data *info)
{
	int	i;
	
	i = 0;
	while (i < info->pipe_count)
	{
		close(info->process[i].fd[0]);
		close(info->process[i].fd[1]);
		i++;
	}
}
