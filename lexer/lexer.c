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

void	*add_space(char *read_line)
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

void	free_lexer(char *read_line, char **read_line_split)
{
	int	i;

	i = -1;
	while (read_line_split[++i])
		free(read_line_split[i]);
	free(read_line_split);
	free(read_line);
}

char	**lexer(char *read_line)
{
	int		i;
	char	*new_line;
	char	**read_line_split;

	i = -1;
	new_line = add_space(read_line);
	read_line_split = ft_split(new_line, " ");
	free(new_line);
	return (read_line_split);
}
