/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:43:11 by museker           #+#    #+#             */
/*   Updated: 2023/10/04 21:27:14 by mucakmak         ###   ########.fr       */
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

# include <signal.h>

# define Q0 0
# define Q1 1
# define Q2 2

typedef struct s_list
{
	void			*key;
	char			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_process
{
	pid_t	pid;
	int		fd[2];
}	t_process;

typedef struct s_commands
{
	char			**commands;
	int				*flags;
}	t_commands;

typedef struct s_data
{
	char			**paths;
	char			**env_p;
	int				pipe_count;
	t_list			*env_lst;
	t_commands		*cmd;
	t_list			*arg;
	t_process		*process;
}	t_data;

// main.c
void		find_path_and_exec(t_data *info, char **read_line);
int			create_fork_and_exec(t_data *info, char **read_line);
void		set_env_p(t_data *info, char **env_p);

// exec/exec_utils.c
void		ft_process_merge(t_data *info, int i);
int			find_pipe_count(t_data *info);
void		pipe_finder(t_data *info, int *count);
void		pipe_close(t_data *info);

// exec/exec.c
void		exec(t_data *info);
int			exec_command(t_data *info, char **read_line, int count, int i);
void		create_fork(t_data *info, char **read_line, int count, int i);
void		find_path_and_exec(t_data *info, char **read_line);
char		**read_line_edit(t_data *info, int index);

// lexer/lexer_str.c
char		*check_dollar(t_data *info, char *s);
void		*dollar_split(t_data *info, char *s, int *in);
void		*no_dollar_split(char *s, int *in);
char		*replace_dollar(t_data *info, char *s);

// lexer/lexer_utils.c
int			pipe_ct(char *read_line);
char		*add_space(char *rd);
int			ft_char_count(char *read_line, int c);
char		**pipe_split(char	*s, char c, int p);
void		pipe_adder(t_data *info, char *str, int *k);
void		lst_combining(t_data *info);
void		two_pointer_free(char **s);

// lexer/lexer.c
void		lexer(t_data *info, char *read_line);
void		quote(t_data *info, char *read_line);
void		quotes(t_data *info, char *read_line, int *index, int c1);
void		no_quote(t_data *info, char *read_line, int *index);
char		*char_combining(char **s);

// utils/lst_all.c
t_list		*ft_lstnew(void *key, void *value);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
void		ft_lstclear(t_list **lst);

// utils/ft_split.c
char		*ft_strchr(const char *s, int c);
int			count_word(const char *p, char c);
char		**ft_split(char const *s, char c);

// utils/ft_str_1.c
size_t		ft_strlen(const char *str);
int			ft_find_index(char *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_before_c(char *s, char c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);

// utils/ft_str_2.c
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
int			find_key(t_data *info, char *s);

// utils/ft_str_3.c
char		*ft_strtrim(char const *s1, char const *set);

#endif