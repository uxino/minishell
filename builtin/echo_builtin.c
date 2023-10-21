/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:23 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/16 19:53:52 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_check_n(t_data *info, char **s, int c)
{
	int	i;
	int	j;

	(void)c;
	(void)info;
	i = 1;
	if (s[i] && s[i][0] != '-')
		return (0);
	while (s[i] && s[i][0] == '-' && s[i][1] == 'n')
	{
		j = 1;
		while (s[i][j])
			if (s[i][j++] != 'n')
				return (i - 1);
		i++;
	}
	return (i - 1);
}

void	echo_builtin(t_data *info, char **s, int c)
{
	int	i;
	int	flag;

	(void)info;
	i = 1;
	if (!s[1])
	{
		printf("\n");
		exit(0);
	}
	flag = echo_check_n(info, s, c);
	if (flag)
		i += flag;
	while (s[i])
	{
		printf("%s", s[i++]);
		if (s[i])
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	exit(0);
}
