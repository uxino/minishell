/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:23 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/04 22:45:14 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_p(t_data *info, char **env_p)
{
	int		i;
	char	**temp;
	t_list	*tmplst_1;

	i = -1;
	info->env_lst = NULL;
	while (env_p[++i])
	{
		temp = ft_split(env_p[i], '=');
		tmplst_1 = ft_lstnew(temp[0], temp[1]);
		ft_lstadd_back(&(info->env_lst), tmplst_1);
		free(temp);
	}
	info->env_p = env_p;
	info->paths = ft_split(getenv("PATH"), ':');
}

int	main(int argc, char *argv[], char **env_p)
{
	t_data		*info;
	char		*read_line;

	info = malloc(sizeof(t_data));
	info->cmd = malloc(sizeof(t_commands));
	info->arg = NULL;
	set_env_p(info, env_p);
	while (1)
	{
		read_line = readline("\033[0;31m(Minishell)$>\033[0m ");
		if (!*read_line)
		{
			free(read_line);
			continue;
		}
		add_history(read_line);
		lexer(info, read_line);
		exec(info);
		two_pointer_free(info->cmd->commands);
		free(info->cmd->flags);
		free(read_line);
		ft_lstclear(&info->arg);
	}
	return (0);
}
