/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:56:01 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/12 00:18:14 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
		g_data->exit_code = 1;
		write(1, "\033[A", 3);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

void	check_sigint(t_data *info, char *rl)
{
	(void)info;
	if (!rl)
	{
		g_data->exit_code = 1;
		exit(1);
	}
}

int	err_message(t_data *info, char *msg)
{
	int	fd;

	(void)info;
	fd = fork();
	if (fd == 0)
	{
		printf("%s\n", msg);
		exit(1);
	}
	else
		wait(&fd);
	g_data->exit_code = 1;
	return (1);
}

void	hg_signal(int sig)
{
	if (sig == SIGINT)
		g_data->hd->flag = 1;
}
