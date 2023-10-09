/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:15:11 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/09 18:34:12 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    exit_builtin(t_data *info, char *rl)
{
    int i;
    int status;

    if (check_builtin_str(info, "exit"))
        return (0);
    i = 0;
    while (info->cmd->commands[i])
        i++;
    if (i > 2)
    {
        printf("Too many arguments\n");
        free_info_and_rl(info, rl);
        return (1);
    }
    printf("exit\n");
    if (i == 2)
    {
        status = ft_atoi(info->cmd->commands[1]);
        exit(status);
    }
    exit(127);
}
