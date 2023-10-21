/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:46 by museker           #+#    #+#             */
/*   Updated: 2023/10/16 16:57:40 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lexer(t_data *info, char *read_line)
{
	int	i;

	if (check_read_line(info, read_line))
		return (1);
	quote(info, read_line);
	lst_info_combining(info);
	i = -1;
	while (info->cmd->commands[++i])
	{
		if (!info->cmd->commands[i][0])
		{
			printf("minishell: : command not found\n");
			free_info_and_rl(info, read_line);
			g_data->exit_code = 1;
			return (1);
		}
	}
	return (0);
}

int	check_read_line(t_data *info, char *rl)
{
	if (!*rl || check_syntax(info, rl) == 1)
	{
		free(rl);
		return (1);
	}
	return (0);
}

void	quote(t_data *info, char *read_line)
{
	int	i;

	i = 0;
	while (read_line[i])
	{
		if (read_line[i] == 39)
			quotes(info, read_line, &i, 39);
		else if (read_line[i] == '"')
			quotes(info, read_line, &i, '"');
		else if ((read_line[i] != '"') || (read_line[i] != '\''))
			no_quote(info, read_line, &i);
	}
}

void	quotes(t_data *info, char *rl, int *index, int c1)
{
	int		start;
	char	*nl;
	int		end;

	end = 0;
	start = ++(*index);
	while (rl[*index])
	{
		if (rl[*index] == c1)
		{
			end = (*index)++;
			break ;
		}
		(*index)++;
	}
	nl = ft_substr(rl, start, end - start);
	if (c1 == '"' && char_c(rl, '$'))
		ft_lstadd_back(&info->arg, ft_lstnew((void *)Q1, check_dollar(info,
					nl)));
	else
		ft_lstadd_back(&info->arg, ft_lstnew((void *)Q1, nl));
}

void	no_quote(t_data *info, char *rl, int *index)
{
	int	start;
	int	end;

	start = *index;
	while (rl[*index])
	{
		if (rl[*index] == '\'' || rl[*index] == '"' || rl[*index] == ' ')
		{
			if (rl[*index] == ' ')
				(*index)++;
			end = *index;
			while (rl[*index] == ' ')
				(*index)++;
			break ;
		}
		(*index)++;
	}
	if (rl[*index - 1] != ' ' && (rl[*index] == '\0'
			&& !(rl[*index - 1] == '\''
				|| rl[*index - 1] == '"')))
		end = *index;
	ft_lstadd_back(&info->arg, ft_lstnew((void *)Q0, check_dollar(info,
				ft_substr(rl, start, end - start))));
}
