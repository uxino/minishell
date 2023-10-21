/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:04:17 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/16 15:05:39 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_ct(char *read_line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (read_line[i])
	{
		if (read_line[i] == '|')
			count++;
		i++;
	}
	return (count * 2);
}

int	char_c(char *read_line, int c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (read_line[++i])
		if (read_line[i] == c)
			count++;
	return (count);
}

char	**pipe_split(char *s, char *str_c, char c, int p)
{
	int		i;
	int		j;
	int		temp;
	char	**str_split;

	i = 0;
	j = 0;
	str_split = (char **)malloc(sizeof(char *) * (count_word(s, c) + p + 1));
	while (s[i])
	{
		if (s[i] && s[i] == c && ++i)
			str_split[j++] = ft_strdup(str_c);
		temp = i;
		while (s[i] && s[i] != c)
			i++;
		if (count_word(s, c) + p == j)
			break ;
		str_split[j++] = ft_substr(s, temp, i - temp);
		if (s[i])
			i++;
		if (count_word(s, c) + p != j)
			str_split[j++] = ft_strdup(str_c);
	}
	str_split[j] = 0;
	return (str_split);
}

void	pipe_adder(t_data *info, char *str, int *k)
{
	int		i;
	char	**split;

	i = -1;
	split = pipe_split(str, "|", '|', char_c(str, '|'));
	while (split[++i])
	{
		info->cmd->commands[++(*k)] = split[i];
		info->cmd->flags[*k] = Q0;
	}
	free(split);
}
