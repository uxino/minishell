/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:40 by museker           #+#    #+#             */
/*   Updated: 2023/10/12 00:05:07 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	find_i(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_before_c(char *s, char c)
{
	int		i;
	int		index;
	char	*result;

	i = -1;
	index = 0;
	if (!s[0])
		return (NULL);
	while (s[++i])
	{
		if (s[i] == c)
		{
			index = i;
			break ;
		}
	}
	result = malloc(index + 1);
	i = -1;
	while (++i < index)
		result[i] = s[i];
	result[i] = 0;
	return (result);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	p;

	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			p = i;
			while (haystack[i] == needle[j] && haystack[i] && i < len)
			{
				i++;
				j++;
			}
			if (!needle[j] && ft_strlen(haystack) == len)
				return ((char *)haystack + p);
			if (ft_strlen(haystack) >= len)
				return (NULL);
			i = p;
		}
		i++;
	}
	return (NULL);
}
