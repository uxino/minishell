/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/12 02:45:57 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec(t_data *info, char *rl)
{
	int	i;
	int	count;

	info->pipe_count = find_pipe_count(info);
	info->process = malloc(sizeof(t_process) * (info->pipe_count + 1));
	i = -1;
	while (++i < info->pipe_count)
		pipe(info->process[i].fd);
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
					return (1);
		}
		i++;
	}
	return (0);
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
		info->hd->flag = heredoc_check(info, count);
		ft_process_merge(info, i);
		new_exec = redirect(info, count);
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
