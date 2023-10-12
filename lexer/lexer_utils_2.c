/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:59:43 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/12 13:17:42 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*char_combining(char **s)
{
	int		i;
	char	*p;
	int		count;
	int		j;
	int		k;

	i = -1;
	k = -1;
	count = 0;
	while (s[++i])
		count += ft_strlen(s[i]);
	i = -1;
	p = malloc(count + 1);
	while (s[++i])
	{
		j = -1;
		while (s[i][++j])
			p[++k] = s[i][j];
	}
	p[++k] = 0;
	return (p);
}

void	lst_info_combining(t_data *info)
{
	int		size;
	int		k;
	t_list	*iter;

	k = -1;
	iter = info->arg;
	size = ft_lstsize(iter) + char_count_lst(info->arg, ' ') + 1;
	info->cmd->commands = malloc(sizeof(char *) * size);
	info->cmd->flags = malloc(sizeof(int) * size);
	while (iter)
	{
		if (ft_char_count(iter->value, '|') && (long)(iter->key) == Q0)
		{
			pipe_adder(info, iter->value, &k);
			free(iter->value);
		}
		else
		{
			info->cmd->commands[++k] = iter->value;
			info->cmd->flags[k] = (long)iter->key;
		}
		iter = iter->next;
	}
	info->cmd->commands[++k] = 0;
	info->cmd->flags[k] = 0;
}

void	two_pointer_free(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

int	char_count_lst(t_list *lst, char c)
{
	int	count;

	count = 0;
	while (lst)
	{
		count += ft_char_count(lst->value, c);
		lst = lst->next;
	}
	return (count);
}
