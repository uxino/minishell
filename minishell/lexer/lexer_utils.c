/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:04:17 by mucakmak          #+#    #+#             */
/*   Updated: 2023/09/24 19:53:01 by mucakmak         ###   ########.fr       */
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

char	*add_space(char *rd)
{
	int		i;
	int		j;
	char	*new_line;

	i = -1;
	j = 0;
	new_line = malloc((ft_strlen(rd) + pipe_ct(rd)));
	while (rd[++i])
	{
		if (rd[i] == '|' || rd[i] == '<' || rd[i] == '>' || rd[i] == '$')
		{
			new_line[i + j++] = ' ';
			new_line[i + j] = rd[i];
			if ((rd[i] && rd[i + 1] && rd[i] == '>' && rd[i + 1] == '>'
					|| rd[i] == '<' && rd[i + 1] == '<')
				&& rd[++i])
				new_line[i + j] = rd[i];
			new_line[i + ++j] = ' ';
			continue ;
		}
		new_line[i + j] = rd[i];
	}
	new_line[i + j] = 0;
	return (new_line);
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


