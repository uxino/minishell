/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:43:11 by museker           #+#    #+#             */
/*   Updated: 2023/09/25 20:24:23 by mucakmak         ###   ########.fr       */
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
	char			**paths;
	char			**env_p;
	t_list			*env_lst;
	t_list			*arg;
}	t_data;

// lexer/lexer.c
char		*quote(t_data *info, char *read_line);
void		quotes(t_data *info, char *read_line, int *index, int c1);
int			pipe_ct(char *read_line);
void		free_lexer(char *read_line, char **read_line_split);
int			ft_char_count(char *read_line, int c);
char		*ft_remove_quotes(char *read_line);
char		**lexer(char *read_line);

// main.c
void		find_path_and_exec(t_data *info, char **read_line);
int			create_fork_and_exec(t_data *info, char **read_line);
void		set_env_p(t_data *info, char **env_p);
char		*replace_dollar(t_data *info, char **s, int index);
char		*check_dollar(t_data *info, char *s);

// utils/lst_all.c
t_list		*ft_lstnew(void *key, void *value);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);

// utils/ft_split.c
char		*ft_strchr(const char *s, int c);
char		*add_space(char *read_line);
size_t		count_word(const char *p, const char *delim);
int			count_str(char *s);
char		**ft_split(const char *s, const char *delim);
char		**ft_split_dollar(const char *s, const char *delim);
char		**ft_split2(const char *s, const char *delim);

// utils/ft_str.c
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_find_index(char *s, char c);
char		*ft_before_c(char *s, char c);

#endif