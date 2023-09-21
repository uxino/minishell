/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:23 by museker           #+#    #+#             */
/*   Updated: 2023/09/19 15:17:24 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_path_and_exec(t_data *info, char **read_line, char **env_p)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = -1;
	while (info->paths[++i])
	{
		tmp2 = ft_strjoin(info->paths[i], "/");
		tmp = ft_strjoin(tmp2, read_line[0]);
		free(tmp2);
		if (access(tmp, F_OK) != -1)
		{
			execve(tmp, read_line, env_p);
			free(tmp);
			exit(42);
		}
		free(tmp);
	}
}

int	create_fork_and_exec(t_data *info, char **read_line, char **env_p)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	pid_t	fork_id;

	i = -1;
	if (!read_line[0])
		return (0);
	fork_id = fork();
	if (fork_id == 0)
	{
		find_path_and_exec(info, read_line, env_p);
		printf("minishell: %s: command not found\n", read_line[0]);
		exit(42);
	}
	else if (fork_id > 0)
		wait(&fork_id);
	return (0);
}

void	set_env_p(t_data *info, char **env_p)
{
	int		i;
	char	**temp;
	t_list	*tmplst_1;
	t_list	*result_lst;

	i = -1;
	while (env_p[++i])
	{
		temp = ft_split(env_p[i], "=");
		tmplst_1 = ft_lstnew(temp[0], temp[1]);
		ft_lstadd_back(&result_lst, tmplst_1);
		free(temp);
	}
	info->env_lst = result_lst;
	info->paths = ft_split(getenv("PATH"), ":");
}

int	main(int argc, char *argv[], char **env_p)
{
	t_data		*info;
	char		**read_line_split;
	char		*read_line;

	info = malloc(sizeof(t_data));
	set_env_p(info, env_p);
	while (1)
	{
		read_line = readline("(Minishell)$> ");
		read_line_split = lexer(read_line);
		add_history(read_line);
		create_fork_and_exec(info, read_line_split, env_p);
		free_lexer(read_line, read_line_split);
	}
	return (0);
}
