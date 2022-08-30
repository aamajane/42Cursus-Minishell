/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 16:56:30 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 18:08:46 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <term.h>

# define STDIN		0
# define STDOUT		1
# define STDERR		2
# define PIPE_END	-42

# define BUF_SIZE	5

# define BLT_ECHO	0
# define BLT_CD		1
# define BLT_PWD	2
# define BLT_EXPORT	3
# define BLT_UNSET	4
# define BLT_ENV	5
# define BLT_EXIT	6
# define NOT_BLT	7

typedef struct s_glob
{
	char	**env;
	char	**exp;
	int		ctrl_c;
	int		exit_code;
	int		child_pro;
	int		open_pipe;
	int		open_hdoc;
	int		cmds_count;
}				t_glob;

typedef struct s_join
{
	char	*pipe_line;
	char	*cmd_line;
	char	*tmp;
	int		dupfd;
}				t_join;

typedef struct s_hdoc
{
	char	*line;
	char	*tmp;
	int		quote;
	int		end[2];
	int		dupfd;
}				t_hdoc;

typedef struct s_cmd
{
	char	**args;
	char	*path;
	int		infd;
	int		outfd;
	int		index;
	pid_t	pid;
}				t_cmd;

typedef struct s_pipex
{
	int	p1_end[2];
	int	p2_end[2];
}				t_pipex;

typedef struct s_exec
{
	t_pipex	pipex;
	int		builtin;
	int		child_pro;
	int		i;
}				t_exec;

typedef struct s_exp
{
	char	**new_env;
	char	**array;
	char	*var_name;
	char	*var;
	char	*tmp;
	int		index;
	int		len;
	int		i;
	int		j;
}				t_exp;

/* ************************************************************************** */
/*		 						global variable								  */
/* ************************************************************************** */

t_glob	g_data;

/* ************************************************************************** */
/*		 							readline								  */
/* ************************************************************************** */

void	rl_replace_line(const char *text, int clear_undo);

/* ************************************************************************** */
/*		 							signals									  */
/* ************************************************************************** */

// signals.c
void	ctrl_backslash_handler(int sig);
void	ctrl_c_handler(int sig);
void	ctrl_d_handler(void);

/* ************************************************************************** */
/*		 							parsing									  */
/* ************************************************************************** */

// parsing.c
t_cmd	*parsing(char **line);
int		double_pointer_length(char **cmds);

// check_quotes_syntax.c
int		check_quotes_syntax(char *line);
int		skip_quotes_content(char *line);

// check_pipes_syntax.c
int		check_pipes_syntax(char *line);
int		check_first_pipe(char *line);

// check_redirections_syntax.c
int		check_redirections_syntax(char *line);
int		check_after_redirections(char *line);

// join_command_line.c
int		join_command_line(char **line);
int		read_open_pipe(t_join *join, char **line);
int		check_last_pipe(char *line);
int		full_spaces(char *str);
int		add_joined_line_to_history(t_join *join, char **line);

// split_command_line.c
char	**split_command_line(char *line);
void	replace_quote_character(char *line, char target, char replacement);

// add_spaces.c
void	add_spaces(char ***full_cmds);
int		added_spaces_count(char *cmd);
char	*copy_command_with_spaces(char *cmd, int spaces_count);
void	copy_spaces(char **sp_cmd, char *cmd, int *j, int *i);
int		copy_quotes_content(char **sp_cmd, char *cmd, int *j, int *i);

// split_commands.c
char	***split_commands(char **full_cmds);
void	reset_commands_quotes_spaces(char ***cmds_array);

/* ************************************************************************** */
/*									expanding								  */
/* ************************************************************************** */

// expanding.c
void	expanding(char ****cmds_array);
void	copy_expanded_argument(char **cmd_array, char **exp_arg);
void	rearrange_array(char ***cmd_array, char *str, int *j);

// remove_quotes.c
char	*expand_and_remove_quotes(char *str);
void	remove_single_quote(char **exp_arg, char *str, int *i, int *j);
void	remove_double_quote(char **exp_arg, char *str, int *i, int *j);
void	duplicate_argument(char **exp_arg, char *str, int *i, int *j);
void	check_expanded_argument(char **exp_arg, char *str, int i);

// expand_variable.c
void	expand_variable(char **exp_arg, char *str, int *i, int *j);
char	*get_variable_name(char *str, int *j);
int		get_variable_name_len(char *str);
void	join_expanded_variable(char **exp_arg, char *var_val, int *i);

// expand_here_doc_variables.c
void	remove_delimiter_qoute(char **str);
void	expand_heredoc_variable(char **line);

/* ************************************************************************** */
/*		 							execution								  */
/* ************************************************************************** */

// get_commands_infos.c
t_cmd	*get_commands_infos(char ***cmds_array);
void	check_commands_errors(t_cmd *cmds);

// get_command_read_fd.c
int		get_command_read_fd(char **full_cmd, int index);
char	*open_file_in_read_mode(int *infd, char *infile);
void	open_heredoc(int *infd, char *infile);
int		heredoc(char *delimiter);
void	read_heredoc_lines(t_hdoc *hdoc, char *delimiter);

// get_command_write_fd.c
int		get_command_write_fd(char **full_cmd, int index);
void	open_file_in_trunc_mode(int *outfd, char *outfile);
void	open_file_in_append_mode(int *outfd, char *outfile);

// get_command_arguments.c
char	**get_command_arguments(char **full_cmd);
int		arguments_count(char **full_cmd);
int		is_not_argument(char **full_cmd, int i);

// get_command_path.c
char	*get_command_path(char *cmd);
char	**get_environment_path(char *cmd);
char	*check_command_path(char *cmd, char **paths);

// execution.c
void	execution(t_cmd *cmds);
void	close_all_fd(t_cmd *cmds, t_pipex *pipex);

// get_command_pipe_fd.c
void	creat_pipes(t_pipex *pipex);
void	get_command_pipe_fd(t_pipex *pipex, t_cmd *cmd);
int		get_pipe_read_fd(t_pipex *pipex, int index);
int		get_pipe_write_fd(t_pipex *pipex, int index);

// child_process.c
void	execute_command(t_cmd *cmd, t_pipex *pipex, int builtin);
void	wait_child_processes(t_cmd *cmds);

/* ************************************************************************** */
/*		 							builtins								  */
/* ************************************************************************** */

// builtin_execution.c
int		command_is_builtin(char *cmd);
void	execute_builtin(t_cmd *cmd, int builtin);
int		get_builtin_value(char **args);

// echo.c
void	builtin_echo(char **args, int outfd);
int		is_n_option(char *arg);

// cd.c
void	builtin_cd(char **args, int outfd);
void	cd_home(char *arg);
void	cd_oldpwd(void);
void	set_oldpwd(void);
void	set_pwd(void);

// pwd.c
void	builtin_pwd(char **args, int outfd);

// export.c
void	builtin_export(char **args, int outfd);
void	print_export(int outfd);
void	sort_export(void);
void	export_variable(char ***env, char *arg);

// export_utils.c
char	*get_export_variable_name(char *arg);
char	*get_export_full_variable(char *arg);
int		join_export_plus_variable_value(char **new_var, char *arg);
int		add_export_plus_variable(char **new_var, char *arg);

// unset.c
void	builtin_unset(char **args, int outfd);
int		check_variable_name(char *var_name);
char	**unset_variable(char **env, char *var_name);

// env.c
void	builtin_env(char **args, int outfd);
char	**duplicate_env(char **str);
char	**duplicate_exp(char **env);
char	*get_variable_value(char **env, char *var_name);
int		get_variable_index(char **env, char *var_name);

// exit.c
void	builtin_exit(char **args, int outfd);

/* ************************************************************************** */
/*		  							error 								  	  */
/* ************************************************************************** */

// error_1.c
int		puterror(char *str);
int		print_syntax_error(char *str);
void	print_command_error(char *str);
void	print_path_error(char *str);

// error_2.c
void	print_cd_error(char *str);
void	print_pwd_error(char c);
void	print_variable_name_error(char *cmd, char *str);
void	print_exit_argument_error(void);
int		print_exit_numeric_error(char *str);

/* ************************************************************************** */
/*		   							free 									  */
/* ************************************************************************** */

// free.c
void	free_commands_data(t_cmd *cmd);
void	free_double_pointer(char **str);
void	free_triple_pointer(char ***str);

#endif
