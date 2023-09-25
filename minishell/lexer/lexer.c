/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:46 by museker           #+#    #+#             */
/*   Updated: 2023/09/25 20:51:04 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quotes(t_data *info, char *read_line, int *index, int c1)
{
	int	i;
	int	start;
	char *new_line;
	char *maybe;
	int	end;
	t_list *tmplst;

	start = ++(*index);
	while (read_line[*index])
	{
		if (read_line[*index] == c1)
		{
			end = (*index)++;
			break;
		}
		(*index)++;
	}
	// tmplst = ft_lstnew(0, new_line);
	new_line = ft_substr(read_line, start, end - start);
	if (c1 == '"' && ft_char_count(new_line, '$'))
		ft_lstadd_back(&(info->arg), ft_lstnew(0, check_dollar(info, new_line)));
	else
		ft_lstadd_back(&(info->arg), ft_lstnew(0, new_line));
	free(new_line);
	// free(tmplst);
}

void	quotes2(t_data *info, char *read_line, int *index)
{
	int	i;
	int	start;
	char *new_line;
	int	end;
	t_list	*tmplst;

	start = *index;
	while (read_line[*index])
	{
		if (read_line[*index] == '\'' || read_line[*index] == '"')
		{
			end = *index;
			break;
		}
		(*index)++;
	}
	if (read_line[*index] == '\0' && !(read_line[*index - 1] == '\'' || read_line[*index - 1] == '"'))
		end = *index;
	// tmplst = ft_lstnew(0, new_line);
	new_line = ft_substr(read_line, start, end - start);
	ft_lstadd_back(&(info->arg), ft_lstnew(0, new_line));
	free(new_line);
	// free(tmplst);
}

char	*quote(t_data *info, char *read_line)
{
    int 	i;

    i = 0;
	info->arg = NULL;
    while (read_line[i])
    {
		if (read_line[i] == 39)
			quotes(info, read_line, &i, 39);
		else if (read_line[i] == 34)
			quotes(info, read_line, &i, 34);
		else if (read_line[i] != 34 || read_line[i] != 39)
			quotes2(info, read_line, &i);
    }
	// while (info->arg)
	// {
	// 	printf("(%s)\n", info->arg->value);
	// 	info->arg = info->arg->next;
	// }
	return (NULL);
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

char	*replace_dollar(t_data *info, char **s, int index)
{
	t_list	*temp;
	char	*temp_str;

	temp = info->env_lst;
	while (temp)
	{
		if (ft_strnstr(temp->key, s[index],
			ft_strlen(s[index])))
		{
			temp_str = ft_strdup(temp->value);
			return (temp_str);
		}
		temp = temp->next;
	}
	if (!temp)
		return(ft_strdup(""));
	temp_str = ft_strdup(s[index]);
	return (temp_str);
}


char	*check_dollar(t_data *info, char *s)
{
	int	i;
	int	j;
	int	z;
	char **str;
	char **str2;
	char **str3;

	str = ft_split(s, "$");
	i = -1;
	z = -1; // "abc de" "123 45"
	str3 = malloc(sizeof(char **) * (count_str(s))); 
	while (str[++i])
	{
		j = -1;
		str2 = ft_split2(str[i], " ");
		while (str2[++j])
		{
			str3[++z] = replace_dollar(info, str2, j);
			printf("{%s}\n", str3[z]);
			free(str3[z]); 
			free(str2[j]);
		}
		free(str2);
		free(str[i]);
	}
	free(str);
	free(str3);
	return (NULL); // çift pointeri tek pointer yap ve return yap
}


void	free_lexer(char *read_line, char **read_line_split)
{
	int	i;

	i = -1;
	// while (read_line_split[++i])
	// 	free(read_line_split[i]);
	// free(read_line_split);
	// free(read_line);
}
