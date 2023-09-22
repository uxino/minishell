/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:43 by museker           #+#    #+#             */
/*   Updated: 2023/09/19 15:19:17 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char	*add_space(char *read_line)
{
	int		i;
	int		j;
	char	*new_line;

	i = -1;
	j = 0;
	new_line = malloc((ft_strlen(read_line) + pipe_ct(read_line)));
	while (read_line[++i])
	{
		if (read_line[i] == '|' || read_line[i] == '<' || read_line[i] == '>')
		{
			new_line[i + j++] = ' ';
			new_line[i + j] = read_line[i];
			if ((read_line[i] && read_line[i + 1]
					&& read_line[i] == '>' && read_line[i + 1] == '>'
					|| read_line[i] == '<' && read_line[i + 1] == '<')
				&& read_line[++i])
				new_line[i + j] = read_line[i];
			new_line[i + ++j] = ' ';
			continue ;
		}
		new_line[i + j] = read_line[i];
	}
	new_line[i + j] = 0;
	return (new_line);
}

size_t	count_word(const char *p, const char *delim)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (p[i])
	{
		while (ft_strchr(delim, p[i]) && p[i])
			i++;
		if (!ft_strchr(delim, p[i]) && p[i])
		{
			len++;
			while (!ft_strchr(delim, p[i]) && p[i])
				i++;
		}
	}
	return (len);
}

char	**ft_split(const char *s, const char *delim)
{
	char	**list;
	size_t	i;
	size_t	tmp;
	size_t	h_y;

	i = 0;
	h_y = 0;
	list = (char **)malloc(sizeof(char *) * (count_word(s, delim) + 1));
	if (!list)
		return (NULL);
	while (s[i])
	{
		while (ft_strchr(delim, s[i]) && s[i])
			i++;
		tmp = i;
		while (!ft_strchr(delim, s[tmp]) && s[tmp])
			tmp++;
		if (count_word(s, delim) == h_y)
			break ;
		list[h_y++] = ft_substr(s, i, tmp - i);
		i = tmp;
	}
	list[h_y] = NULL;
	return (list);
}
