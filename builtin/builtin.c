/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/16 15:06:20 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin_str(t_data *info, char *str)
{
	char	*s;
	int		i;

	i = -1;
	while (info->cmd->commands[++i])
		if (char_c(info->cmd->commands[i], '|'))
			return (1);
	if (info->cmd->flags[0] == Q0)
	{
		s = ft_strtrim(info->cmd->commands[0], " ");
		if (!ft_strcmp(s, str))
		{
			free(s);
			return (0);
		}
		free(s);
	}
	else if (!ft_strcmp(info->cmd->commands[0], str))
		return (0);
	return (1);
}

int	syntax_return(t_data *info, char *s, t_list *sa, char *rl)
{
	free_info_and_rl(info, rl);
	free(s);
	ft_lstclear(&sa);
	return (1);
}

int	pwd_builtin(t_data *info)
{
	char	*s;

	(void)info;
	s = getcwd(NULL, 0);
	printf("%s\n", s);
	free(s);
	g_data->exit_code = 124;
	exit(0);
}

int	main_builtin(t_data *info, char *rl)
{
	if (add_export(info, rl))
		return (1);
	if (exit_builtin(info, rl))
		return (1);
	if (cd_builtin(info, rl))
		return (1);
	if (unset_builtin(info, rl))
		return (1);
	return (0);
}

void	child_builtin(t_data *info, char **s, int count)
{
	if (!ft_strcmp(s[0], "echo"))
		echo_builtin(info, s, count);
	else if (!ft_strcmp(s[0], "export"))
		export_builtin(info);
	else if (!ft_strcmp(s[0], "env"))
		env_builtin(info);
	else if (!ft_strcmp(s[0], "pwd"))
		pwd_builtin(info);
}
