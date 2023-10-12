/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:23 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/12 15:28:14 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **env_p)
{
	t_data	*info;
	char	*read_line;

	(void)argc;
	(void)argv;
	info = ft_initializer();
	set_env_p(info, env_p);
	while (1)
	{
		read_line = readline("\033[0;31m(Minishell)$>\033[0m ");
		add_history(read_line);
		check_sigint(info, read_line);
		if (lexer(info, read_line) || main_builtin(info, read_line))
			continue ;
		exec(info, read_line);
	}
	return (0);
}

t_data	*ft_initializer(void)
{
	t_data	*info;

	signal(SIGINT, ft_sig_handler);
	info = malloc(sizeof(t_data));
	info->cmd = malloc(sizeof(t_commands));
	info->hd = malloc(sizeof(t_heredoc));
	info->arg = NULL;
	info->env_lst = NULL;
	info->export_lst = NULL;
	g_data = malloc(sizeof(t_data));
	g_data->hd = malloc(sizeof(sizeof(t_heredoc)));
	g_data->hd->flag = 0;
	return (info);
}

void	set_env_p(t_data *info, char **env_p)
{
	int		i;
	char	**temp;
	char	*tmp;
	t_list	*tmplst_1;
	t_list	*tmplst_2;

	i = -1;
	while (env_p[++i])
	{
		temp = ft_split(env_p[i], '=');
		tmplst_1 = ft_lstnew(ft_strdup(temp[0]), ft_strdup(temp[1]));
		ft_lstadd_back(&(info->env_lst), tmplst_1);
		tmplst_2 = ft_lstnew(ft_strdup(temp[0]), ft_strdup(temp[1]));
		ft_lstadd_back(&(info->export_lst), tmplst_2);
		two_pointer_free(temp);
	}
	info->env_p = env_p;
	tmp = getenv("PATH");
	if (tmp)
		info->paths = ft_split(tmp, ':');
	else
		info->paths = ft_split(" ", ' ');
}

int	free_info_and_rl(t_data *info, char *rl)
{
	two_pointer_free(info->cmd->commands);
	free(info->cmd->flags);
	free(rl);
	ft_lstclear(&info->arg);
	return (1);
}
