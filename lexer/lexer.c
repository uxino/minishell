/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:46 by museker           #+#    #+#             */
/*   Updated: 2023/09/19 15:17:47 by museker          ###   ########.fr       */
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

void	free_lexer(char *read_line, char **read_line_split)
{
	int	i;

	i = -1;
	while (read_line_split[++i])
		free(read_line_split[i]);
	free(read_line_split);
	free(read_line);
}

int	ft_char_count(char *read_line, int c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while(read_line[++i])
		if (read_line[i] == c)
			count++;
	return (count);
}

char	*ft_remove_quotes(char *read_line)
{
	int		i;
	int		j;
	char	*s;

	if (ft_char_count(read_line, 34) % 2 == 1 
			|| ft_char_count(read_line, 39) % 2 == 1)
		return (NULL);
	i = -1;
	j = -1;
	s = malloc(sizeof(char) * (ft_strlen(read_line) - 
			ft_char_count(read_line, 34) - ft_char_count(read_line, 39) + 1)); // 
	while(read_line[++i])
	{
		if (read_line[i] == 34 || read_line[i] == 39)
			continue;
		s[++j] = read_line[i];
	}
	s[++j] = 0;
	return (s);
}

char	**lexer(char *read_line)
{
	char	*removed_quotes;
	char	*new_line;
	char	**read_line_split;

	removed_quotes = ft_remove_quotes(read_line);
	if (removed_quotes == NULL)
		new_line = add_space(read_line);
	else
	{
		new_line = add_space(removed_quotes);
		free(removed_quotes);
	}
	read_line_split = ft_split(new_line, " ");
	free(new_line);
	return (read_line_split);
}
