/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:43:11 by museker           #+#    #+#             */
/*   Updated: 2023/09/19 15:19:04 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_commands
{
	char			**commands;
	int				fd[2];
}	t_commands;

typedef struct s_data
{
	int				number_of_arguments;
	int				number_of_avaible_arguments;
	char			**arguments;
	char			**paths;
	t_list			*env_lst;
}	t_data;

// lexer/lexer.c
char		**lexer(char *read_line);
void		*add_space(char *read_line);
void		free_lexer(char *read_line, char **read_line_split);

// main.c
void		find_path_and_exec(t_data *info, char **read_line, char **env_p);
int			create_fork_and_exec(t_data *info, char **read_line, char **env_p);

// utils/lst_all.c
t_list		*ft_lstnew(void *key, void *value);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);

// utils/ft_split.c
char		*ft_strchr(const char *s, int c);
size_t		count_word(const char *p, const char *delim);
char		**ft_split(const char *s, const char *delim);

// utils/ft_str.c

size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strncmp(const char *s1, const char *s2);
char		*ft_strjoin(char const *s1, char const *s2);

#endif