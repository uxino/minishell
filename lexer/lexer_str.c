/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:43 by museker           #+#    #+#             */
/*   Updated: 2023/10/07 20:30:45 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_dollar(t_data *info, char *s)
{
	int		i;
	int		z;
	char	**new;
	char	*temp;
	char	*km;

	i = 0;
	z = -1;
	new = (char **)malloc(sizeof(char *) * (ft_strlen(s) + 1));
 	while (s[i])
	{
		if (s[i] == '$')
			temp = dollar_split(info, s, &i);
		else
			temp = no_dollar_split(s, &i);
		new[++z] = temp;
	}
	new[++z] = 0;
	km = char_combining(new);
	two_pointer_free(new);
	free(s);
	return (km);
}

void	*dollar_split(t_data *info, char *s, int *in)
{
	int		tmp;
	int		tmp2;
	char	*char_tmp;
	char	*char1;

	(*in)++;
	if (s[*in] == '$' || s[*in] == ' ' || !s[*in])
		return (ft_strdup("$"));
	tmp = *in;
	while (s[*in] && s[*in] != '$' && s[*in] != ' ')
		(*in)++;
	tmp2 = *in;
	char_tmp = ft_substr(s,tmp, tmp2 - tmp);
	if (find_key(info, char_tmp))
	{
		char1 =	replace_dollar(info, char_tmp);
		free(char_tmp);
		return (char1);
	}
	else
		free(char_tmp);
	return (ft_strdup(""));
}

void	*no_dollar_split(char *s, int *in)
{
	char 	*new;
	int		cpy_in;

	cpy_in = *in;
	while (s[cpy_in])
	{
		if (s[cpy_in] == '$' || s[cpy_in] == ' ')
			break ;
		cpy_in++;
	}
	if (s[cpy_in] == ' ')
		cpy_in++;
	new = ft_substr(s, *in, cpy_in - *in);
	*in = cpy_in;
	return (new);
}

char	*replace_dollar(t_data *info, char *s)
{
	t_list	*temp;
	char	*temp_str;

	temp = info->env_lst;
	while (temp)
	{
		if (ft_strnstr(temp->key, s,
			ft_strlen(s)))
		{
			temp_str = ft_strdup(temp->value);
			return (temp_str);
		}
		temp = temp->next;
	}
	if (!temp)
		return(ft_strdup(""));
	temp_str = ft_strdup(s);
	return (temp_str);
}
