/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:56:01 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/16 16:38:24 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	suppress_output(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p) != 0)
		perror("Minishell: tcgetattr");
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_p) != 0)
		perror("Minishell: tcsetattr");
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT && g_data->check_fork == 0)
	{
		(void)sig;
		g_data->exit_code = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGINT && g_data->check_fork == 1)
	{
		write(1, "\n", 1);
		g_data->exit_code = 1;
		exit(1);
	}
}

void	check_sigint(t_data *info, char *rl)
{
	(void)info;
	if (!rl)
	{
		g_data->exit_code = 1;
		printf("exit");
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
