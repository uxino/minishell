/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:04:17 by mucakmak          #+#    #+#             */
/*   Updated: 2023/10/16 19:53:52 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	go_next_qoute(char *r, int *i)
{
	while (r[*i])
	{
		if (r[*i] == '\'')
		{
			(*i)++;
			while (r[*i] && r[*i] != '\'')
				(*i)++;
			if (r[*i] == '\'' && (*i)++)
				return (0);
			else
				return (1);
		}
		else if (r[*i] == '"')
		{
			(*i)++;
			while (r[*i] && r[*i] != '"')
				(*i)++;
			if (r[*i] == '"' && (*i)++)
				return (0);
			else
				return (1);
		}
		break ;
	}
	return (0);
}

int	check_pipe(char *r)
{
	int	i;
	int	tmp;

	i = 0;
	while (r[i])
	{
		tmp = 0;
		while (r[i] && (r[i] == ' ' || r[i] == '|'))
		{
			if (r[i] == '|' && ++tmp && tmp >= 2)
				return (1);
			i++;
		}
		while (r[i] && r[i] != ' ' && r[i] != '|' && r[i] != '"'
			&& r[i] != '\'')
			i++;
		if (go_next_qoute(r, &i))
			return (1);
	}
	return (0);
}

int	find_redirect(char *s, char c, char d)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] && s[i + 1] && ((s[i] == c && s[i + 1] == d) || (s[i] == d
					&& s[i + 1] == c)))
			return (1);
		if (s[i] && s[i + 1] && s[i + 2] && s[i] == c && s[i + 1] == c
			&& (s[i + 2] == d || s[i + 2] == c))
			return (1);
	}
	return (0);
}

int	check_redirect(char *rl)
{
	int	i;

	if (find_redirect(rl, '>', '<'))
		return (1);
	i = 0;
	while (rl[i])
	{
		while (rl[i] && (rl[i] == '>' || rl[i] == '<'))
			i++;
		while (rl[i] && rl[i] == ' ')
			i++;
		if (rl[i] && (rl[i] == '>' || rl[i] == '<' || rl[i] == '|'))
			return (1);
		while (rl[i])
		{
			if (rl[i] == '>' || rl[i] == '<')
				break ;
			i++;
		}
	}
	return (0);
}

int	check_syntax(t_data *info, char *rl)
{
	char	*s;
	int		l;

	s = ft_strtrim(rl, " ");
	l = ft_strlen(s) - 1;
	if (s[l] == '|' || s[l] == '>' || s[l] == '<' || s[0] == '|')
	{
		free(s);
		return (err_message(info,
				"minishell: syntax error near unexpected token"));
	}
	free(s);
	if (check_pipe(rl))
		return (err_message(info,
				"minishell: syntax error near unexpected token"));
	if (check_redirect(rl))
		return (err_message(info,
				"minishell: syntax error near unexpected token"));
	return (0);
}
