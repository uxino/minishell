/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/13 18:07:58 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec(t_data *info, char *rl)
{
	int	i;
	int	count;

	info->pipe_count = find_pipe_count(info);
	info->process = malloc(sizeof(t_process) * (info->pipe_count + 1));
	info->hd = malloc(sizeof(t_heredoc) * (info->pipe_count + 1));
	i = -1;
	while (++i < info->pipe_count)
		pipe(info->process[i].fd);
	i = -1;
	while (++i < info->pipe_count + 1)
		pipe(info->hd[i].fd);
	i = -1;
	count = 0;
	while (++i < info->pipe_count + 1)
	{
		exec_command(info, info->cmd->commands + count, count, i);
		pipe_finder(info, &count);
	}
	pipe_close(info);
	while (waitpid(-1, &g_data->exit_code, 0) > 0)
		;
	free_info_and_rl(info, rl);
	free(info->process);
	free(info->hd);
}

int	exec_command(t_data *info, char **read_line, int count, int i)
{
	if (!read_line[0])
		return (0);
	create_fork(info, read_line, count, i);
	return (0);
}

int	heredoc_check(t_data *info, int i)
{
	int		j;
	char	**s;
	int		count;

	count = 0;
	s = info->cmd->commands;
	while (s[i])
	{
		j = -1;
		if (info->cmd->flags[i] == Q0)
		{
			if (ft_char_count(s[i], '|'))
				break ;
			while (s[i][++j])
				if (s[i][j] == '<' && s[i][j + 1] == '<')
					count++;
		}
		i++;
	}
	return (count);
}

void	create_fork(t_data *info, char **read_line, int count, int i)
{
	char	**new_exec;
	pid_t	fork_id;

	(void)read_line;
	fork_id = fork();
	if (fork_id == -1)
		exit(42);
	if (fork_id == 0)
	{
		info->hd[i].flag = heredoc_check(info, count);
		new_exec = redirect(info, count, i);
		ft_process_merge(info, i);
		child_builtin(info, new_exec, count);
		find_path_and_exec(info, new_exec);
		printf("minishell: %s: command not found\n", new_exec[0]);
		exit(127);
	}
}

void	find_path_and_exec(t_data *info, char **rl)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = -1;
	while (info->paths[++i])
	{
		tmp2 = ft_strjoin(info->paths[i], "/");
		tmp = ft_strjoin(tmp2, rl[0]);
		free(tmp2);
		if (access(tmp, F_OK) != -1)
		{
			execve(tmp, rl, info->env_p);
			free(tmp);
		}
		free(tmp);
	}
	if (access(rl[0], F_OK) != -1)
	{
		execve(rl[0], rl, info->env_p);
	}
}
