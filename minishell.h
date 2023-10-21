/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:43:11 by museker           #+#    #+#             */
/*   Updated: 2023/10/16 15:05:39 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

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

typedef struct s_heredoc
{
	int				flag;
	int				fd[2];
}	t_heredoc;

typedef struct s_data
{
	char			**paths;
	char			**env_p;
	int				pipe_count;
	t_list			*env_lst;
	t_list			*export_lst;
	int				exit_code;
	t_commands		*cmd;
	t_list			*arg;
	t_process		*process;
	t_heredoc		*hd;
	int				check_fork;
}	t_data;

t_data	*g_data;

// ------------------main-------------- //

// main.c
t_data		*ft_initializer(void);
void		set_env_p(t_data *info, char **env_p);
int			free_info_and_rl(t_data *info, char *rl);

// ------------------builtin-------------- //

// builtin.c
int			check_builtin_str(t_data *info, char *str);
int			syntax_return(t_data *info, char *s, t_list *sa, char *rl);
int			pwd_builtin(t_data *info);
int			main_builtin(t_data *info, char *rl);
void		child_builtin(t_data *info, char **s, int count);

// cd_builtin_utils.c
void		pwd_changer(t_list *lst);
void		old_pwd_and_pwd_changer_2(t_list *tmp, t_list *pwd);
void		old_pwd_and_pwd_changer(t_list *lst);

// cd_builtin.c
char		*find_key_and_get_char(t_list *lst, char *s);
t_list		*and_get_lst(t_list *lst, char *s);
int			set_home(t_data *info);
int			cd_builtin_2(t_data *info, char *rl);
int			cd_builtin(t_data *info, char *rl);

// echo_builtin.c
int			echo_check_n(t_data *info, char **s, int c);
void		echo_builtin(t_data *info, char **s, int c);

// exit_builtin.c
int			exit_builtin(t_data *info, char *rl);

// export_builtin_utils.c
void		export_is_path(t_data *info, char *s, char *p);
int			check_valid(char *s1, char *s2, int i);
void		change_export(t_data *info, char *s);
int			export_control_and_change(t_list *info, char *s, char *p, int i);

// export_builtin.c
void		export_builtin(t_data *info);
int			export_syntax(t_data *info);
void		env_builtin(t_data *info);
int			add_export(t_data *info, char *rl);
int			err_export(t_data *info, char **s, t_list *tlst);

// signals.c
void		suppress_output(void);
void		ft_sig_handler(int sig);
void		check_sigint(t_data *info, char *rl);
int			err_message(t_data *info, char *msg);

// unset_builtin.c
void		unset_is_path(t_data *info, t_list *path_lst);
void		unset_clear(t_data *info, t_list **lst, char *s);
void		unset_run(t_data *info, char *s);
int			unset_syntax(t_data *info);
int			unset_builtin(t_data *info, char *rl);

// ------------------exec-------------- //

// exec.c
void		exec(t_data *info, char *rl);
int			exec_command(t_data *info, char **read_line, int count, int i);
int			heredoc_check(t_data *info, int i);
void		create_fork(t_data *info, char **read_line, int count, int i);
void		find_path_and_exec(t_data *info, char **rl);

// exec_utils.c
void		is_directory_exit(char *s, char *rl, int a);
void		is_directory(t_data *info, char **rl);

// pipes.c
void		ft_process_merge(t_data *info, int i);
int			find_pipe_count(t_data *info);
void		pipe_finder(t_data *info, int *count);
void		pipe_close(t_data *info);

// redirect_utils.c
void		overwrite_output(t_data *info, t_list *lst);
void		append_output(t_data *info, t_list *lst);
void		overwrite_input(t_data *info, t_list *lst);
void		append_input(t_data *info, t_list *lst, int i);
void		lst_run_redirect(t_data *info, t_list **lst, int i);

// redirect.c
void		redirect_split(t_data *info, t_list **lst, char *s, int in);
void		lst_add_redirect(t_data *info, t_list **lst, int i);
t_list		*go_redirect(t_list *lst);
char		*rd_last_str(t_list *lst);
char		**redirect(t_data *info, int count, int i);

// utils.c
int			get_index(char *s, int c, int q);
t_list		*new_lst(t_list *lst);
int			get_str_size(t_list *lst);
char		*get_str(t_list *lst);
char		**lst_redirect_combining(t_list *lst);

// ------------------lexer-------------- //

// check_syntax.c
int			go_next_qoute(char *r, int *i);
int			check_pipe(char *r);
int			find_redirect(char *s, char c, char d);
int			check_redirect(char *rl);
int			check_syntax(t_data *info, char *rl);

// lexer_str.c
char		*check_dollar(t_data *info, char *s);
void		*dollar_split(t_data *info, char *s, int *in);
void		*no_dollar_split(char *s, int *in);
char		*replace_dollar(t_data *info, char *s);

// lexer_utils_2.c
char		*char_combining(char **s);
void		lst_info_combining(t_data *info);
void		two_pointer_free(char **s);
int			char_count_lst(t_list *lst, char c);

// lexer_utils.c
int			pipe_ct(char *read_line);
int			char_c(char *read_line, int c);
char		**pipe_split(char *s, char *str_c, char c, int p);
void		pipe_adder(t_data *info, char *str, int *k);

// lexer.c
int			lexer(t_data *info, char *read_line);
int			check_read_line(t_data *info, char *rl);
void		quote(t_data *info, char *read_line);
void		quotes(t_data *info, char *rl, int *index, int c1);
void		no_quote(t_data *info, char *rl, int *index);

// ------------------utils-------------- //

// ft_nbr.c
int			ft_atoi(const char *nptr);
void		ft_putchar_fd(char c, int fd);
int			ft_nbrlen(int n);
char		*ft_itoa(int n);

// ft_split.c
char		*ft_strchr(const char *s, int c);
int			count_word(const char *p, char c);
char		**ft_split(char const *s, char c);

// ft_str_1.c
size_t		ft_strlen(const char *str);
int			find_i(char *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_before_c(char *s, char c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);

// ft_str_2.c
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
int			find_key(t_data *info, char *s);

// ft_str_3.c
char		*ft_strtrim(char const *s1, char const *set);
void		ft_putstr_fd(char *s, int fd);

// lst_all.c
t_list		*ft_lstnew(void *key, void *value);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
void		ft_lstclear(t_list **lst);

#endif