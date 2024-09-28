/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:21:08 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/28 11:02:38 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAILED 0
# define PATH_MAX	4096
# define LLONG_MAX 9223372036854775807
# define NO_REDIRECT -1

//errors

# define INTERRUPT 128
# define CMD_NOT_FOUND 127
# define PERMISSION_DENIED 126
# define NOT_EXECUTABLE 126
# define OUT_OF_RANGE 255
# define BUILTIN_MISUSE 2
# define FORK_ERROR -1
# define CMD_NOT_FOUND_MSG	"command not found"
# define NOT_EXECUTABLE_MSG "Is a directory"

//executes

# define IN 0
# define OUT 1

# include <stdio.h> // perror
# include <readline/readline.h> // readline
# include <readline/history.h> // history
# include <stdlib.h> // getenv
# include <unistd.h> // environ, getpwd
# include <sys/wait.h> // waitpid
# include <sys/stat.h> // stat
# include <signal.h> // sigaction
# include <fcntl.h> // open flags

# include "../extra_libs/Libft/libft.h"

typedef struct s_env
{
	char			*key_pair;
	struct s_env	*next;
}	t_env;

char		*get_rposition(char *str);

// buildins

int			cd(char **av, t_env *minienv);
int			echo(char **av);
int			env(t_env *minienv);
int			builtin_exit(char **av, t_env **minienv);
int			pwd(void);
int			unset(char **av, t_env **minienv);
int			builtin_export(char **av, t_env **minienv);

int			is_valid_varname(char *name);

// builtin_exec.c

int			execute_builtin(char **av, t_env **minienv);
int			is_builtin(char *cmd);

// child_redir.c

int			execute_forked_builtin(char **args, t_env **minienv);
void		execute_fork_cmd(char *command, char **commands, t_env **minienv);
void		quit_child(char **commands, t_env **minienv);
void		handle_child_redir(char *command, char **commands, t_env **minienv);

// error_msg.c

int			syntax_error(char *token);
void		print_perror_msg(char *command, char *perror_msg);
void		print_error_msg(char *command, char *msg);
void		exit_with_error(char *command, char *msg, int error);
void		print_varname_error_msg(char *command, char *varname);

// exec_fork_extern.c

void		define_execute_signals(int child_pid);
int			exec_fork_extern(char **av, t_env *minienv);

// expand_input.c

char		*find_var_position(char *input);
char		*find_exit_status_position(char *input);
void		expand_exit_status(char **input, int exit_status);
void		expand_input(char **input, t_env *minienv, int exit_status);

// external_exec.c

int			is_path(char *command);
void		external_exit(char **av, t_env *minienv, int exit_status);
int			is_empty(char *str);
void		execute_external(char **av, t_env *minienv);
char		**minienv_to_envp(t_env *minienv);

// fd_handler.c

void		close_all_fds(void);
void		close_extra_fds(void);

// free_utils.c

char		*free_spaces(char *input);
void		free_array(char **av);
void		m_del_node(t_env **node);

// get_path.c

char		*get_path(char *command, t_env *minienv);

// heredoc_e.c

void		insert_string(char **input, char *var_value, char *rest_str);
char		*var_position(char *s);
void		expand_heredoc(char **input, int exit_status, t_env *minienv);
void		read_heredoc(int *exit_status, t_env *minienv, char *delimiter);

// heredoc_handler.c

int			delimiter_len(char *s);
char		*get_delimiter(char *delim_pos);
char		*get_heredoc_pos(char *str);
int			exec_heredoc(char *delimiter, int *exit_status,
				t_env *minienv, char *input);
int			heredoc_handler(char *input, int *exit_status, t_env *minienv);

// init_minienv.c

t_env		*minienv_node(char *name, t_env *minienv);
char		*value_only(char *key_pair);
char		*minienv_value(char *name, t_env *minienv);
void		minienv_add(char *key_pair, t_env **minienv);
t_env		*init_minienv(char **environ);

// multiple_command.c

void		handle_pipe(int original_fd_out, char *curr_cmd, char **commands);
int			arr_len(char **arr);
int			*init_children_pid(char **commands);
int			multiple_commands(char **commands, t_env **minienv);

// parser.c

char		*skip_quotes(char *str);
int			unclosed_quotes(char *input);
char		*trim_spaces_no_free(char	*input);
int			input_error(char *input, int *exit_status, t_env *minienv);
void		check_av_error(char **av);

// pipe.c

int			has_pipe(char *str);
int			pipe_start(char *input);
int			empty_pipe(char *input);

// redirect_io.c

void		redirect_fd(int fd_to_redirect, int fd_location);
void		save_original_fd(int original_fds[2], int fd_index);
int			redirect_input(char *input);
int			redirect_output(char *command);
int			handle_io(char *command, int original_fds[2], int fd_type);

// redirect.c

void		restore_original_fds(int original_fds[2]);
char		*get_spos(char *str, const char *chars_to_find);
int			unexpected_token(char *input);
char		*get_rposition(char *str);
char		*get_redirect_position(char *str, char redirect_char);
int			redirect_error(char *input);
int			handle_redirects(char *input, int original_fds[2]);

// scanner.c

char		**split_av(char *input);

// signal_handler.c

int			handle_signal_interrupt(int status, int is_last_child);
int			wait_for_child(int child_pid, int is_last_child);
void		define_heredoc_signals(int child_pid);
void		signal_handler(void);

// pipe.c

char		**split_commands(char *input);

// utils.c

int			fits_in_long_long(char *str);
int			is_command(char *str1, char *str2);
void		delete_char(char *str, int len);
long long	ft_atoll(const char *str);
void		redirect_heredoc(char *command);
char		*create_keypair(char *name, char *value);
void		minienv_update(char *name, char *value, t_env *minienv);

#endif
