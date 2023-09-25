/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:43 by museker           #+#    #+#             */
/*   Updated: 2023/09/25 20:01:41 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_split2(const char *s, const char *delim)
{
	char	**list;
	size_t	i;
	size_t	tmp;
	size_t	h_y;
	int		count;

	count = 0;
	i = 0;
	h_y = 0;
	list = (char **)malloc(sizeof(char *) * (count_word(s, delim) + 2));
	if (!list)
		return (NULL);
	while (s[i])
	{
		tmp = i;
		while (ft_strchr(delim, s[tmp]) && s[tmp])
			tmp++;
		while (!ft_strchr(delim, s[tmp]) && s[tmp])
			tmp++;
		if (count_word(s, delim) + 1 == h_y)
			break ;
		list[h_y++] = ft_substr(s, i, tmp - i);
		i = tmp;
	}
	list[h_y] = NULL;
	return (list);
}

int		count_str(char *s)
{
	int	i;
	int	j;
	char **s1;
	char **s2;
	int	count;

	i = -1;
	s1 = ft_split(s, "$");
	while (s1[++i])
	{
		j = -1;
		s2 = ft_split(s1[i], " ");
		while (s2[++j])
		{
			count++;
			free(s2[j]);
		}
		free(s2);
		free(s1[i]);
	}
	free(s1);
	return (count + 1);
}