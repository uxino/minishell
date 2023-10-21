/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/16 19:53:52 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_directory_exit(char *s, char *rl, int a)
{
	printf("minishell: %s: %s\n", s, rl);
	exit(a);
}

void	is_directory(t_data *info, char **rl)
{
	struct stat	*sb;
	int			stat_int;

	(void)info;
	sb = malloc(sizeof(struct stat));
	stat_int = stat(rl[0] + 2, sb);
	if (stat_int == -1)
		is_directory_exit(rl[0], "No such file or directory", 127);
	else
	{
		if (S_ISDIR(sb->st_mode))
			is_directory_exit("is a directory", rl[0], 126);
		else
		{
			if (access(rl[0] + 2, X_OK))
				is_directory_exit("Permission denied", rl[0], 126);
			else
				perror("minishell: ");
			exit(1);
		}
	}
}
