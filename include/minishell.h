/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:48:52 by splattje          #+#    #+#             */
/*   Updated: 2024/03/20 07:38:30 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>
# include <limits.h>
# include <errno.h>
# include "../libft/libft.h"

# define CMD 0
# define INFILE 1
# define OUTFILE 2
# define HERE_DOC 3
# define VAR_DEF 4
# define PIPE 5
# define QUOTE 6
# define OUT_APP 7

# define READ 0
# define WRITE 1

typedef struct s_parts
{
	char			*str;
	int				keep;
	struct s_parts	*next;
}					t_parts;

typedef struct s_lex
{
	char			*str;
	int				sort;
	int				nr;
	t_parts			*parts;
	struct s_lex	*next;
}				t_lex;

typedef struct s_parse
{
	char			**argv;
	char			*cmd_path;
	int				sort;
	int				file;
	int				nr;
	int				pipe_nr;
	struct s_parse	*next;
}					t_parse;

typedef struct s_pipe
{
	int				nr;
	int				pipe[2];
	struct s_pipe	*next;
}					t_pipe;

typedef struct s_var
{
	char			*value;
	struct s_var	*next;
}					t_var;

typedef struct s_check
{
	int	infile;
	int	outfile;
	int	here_doc;
	int	pipes;
	int	var;
	int	var_def;
	int	new_line;
}		t_check;

typedef struct s_mini
{
	t_lex	*lex;
	t_parse	*token;
	t_var	*var;
	t_var	*local;
	t_pipe	*pipe;
	t_check	check;
	char	**envp_path;
	char	**save_path;
	int		in;
	int		out;
	int		save_in;
	int		save_out;
}			t_mini;

// START_END
// main
void	add(int nr);
// set_mini
int		memset_all(t_mini *mini, int argc, char **argv);
int		clean(t_mini *mini, int exit_value);
// first checks
int		empty_line(char *str);
int		first_checks(char *str);
char	*check_last_pipe(char *str, int *exit_value);
// error
void	ft_error(char *str1, char *error, char *str2, int fault);
void	print_error_heredoc(char *limiter, int i);
void	*line_error(int *exit_value);
// exit
int		free_all(t_mini *mini);
int		get_exit_code(t_parse *token);
// free
void	free_parse(t_mini *mini);
void	free_pipes(t_mini *mini);
void	free_lexer(t_mini *mini);
void	free_split(char **split);
void	free_parts(t_lex *lex);
void	free_var(t_var *var);

// SETTINGS
// settings
int		settings(t_mini *mini);
// envp
int		get_paths(t_mini *mini, t_var *var);
// pipes
int		set_pipes(t_mini *mini);
void	close_pipes(t_mini *mini);
int		check_pipes(t_mini *mini);
// in & output
int		get_input(t_mini *mini);
int		get_output(t_mini *mini);
// variables_utils.c
t_var	*var_add_back(t_var *head, t_var *new);
t_var	*new_var(char *data);
int		add_var(t_mini *mini);
char	*join_and_free(char *str1, char *str2);
// keys
void	handle_signals(int signal);
void	handle_heredoc(int signal);
void	handle_signals_child(int signal);
void	handle_signal_parent(int signal);
void	handle_heredoc_parent(int signal);
// local var
int		check_local_var(t_mini *mini);
char	*check_locals(t_mini *mini, char *str);

// LEXER_PARSER
// lexer
int		lexer(t_mini *mini, char *l);
// lexer_substr
char	*make_sort_1(char *l, int i, t_lex *lexer);
char	*make_sort_3(char *l, int i, t_lex *lexer);
char	*make_sort_4(char *l, int i, t_lex *lexer);
// newl_echo
void	check_newline_echo(t_mini *mini, char *line);
// parser
int		parser(t_mini *mini);
// void	set_parser(t_mini *mini);
char	**split_cmd(t_parse *token, int i);
// lexpars_utils
t_lex	*new_lexer(void);
t_parse	*new_parse(int nr);
void	clean_line(char *line, int i, int j);
void	count_sorts(t_mini *mini);

// PARTS
// handle / merge / var / proces
int		handle_parts(t_mini *mini);
int		merge_parts(t_mini *mini, int sort);
int		handle_var(t_mini *mini, int *r_value);
t_var	*set_var(char **envp);
int		proces_parts(t_lex *lexer);
// parts_utils
int		space_handling(int *space);
t_parts	*add_parts(t_parts *parts, char *str, int i);
t_parts	*part_addback(t_parts *parts, char *str);
int		first_part_is_cmd(t_parts *parts);
int		check_brackets(char *str);

// EXECUTOR
// executables
int		executor(t_mini *mini, int i, int round);
// copy_data
char	**make_copy_envp(t_var *var, int len, int i);
t_parse	make_copy_parse(t_parse *token);
// child
int		child_proces(t_mini *mini, t_parse *current);
// utils ex
int		is_in_envp(t_parse *token, char **envp);
void	close_in_out(t_mini *mini);
void	wait_for_child(int i);
// path_checker
char	*find_path(char **envp);
char	*pathfinder(t_mini *mini, char **envp, char *cmd);
char	*pathfinder_abs(char **envp, char *rel_path, char *cmd);
// cd
int		cd(t_parse *token, t_var *envp);
int		change_envp_dir(char *full_path, t_var *envp, int option);
int		print_pwd(t_mini *mini);
int		print_environment(t_mini *mini, t_var *envp);
// builtins utils
int		check_var(t_var *var, t_parse *token);
int		check_amount_dir(t_parse *token);
// unset.c
int		unset_env_var(t_parse *unset_tok, t_var *var);
// echo.c
int		print_echo(t_mini *mini, t_parse *token);
// export.c
int		print_export(t_mini *mini, char *str, t_parse *token);
// cd_utils.c
int		pwd_not_found(t_var *head, char *pwd);
int		goto_old_pwd(t_var *head, t_parse *token);

#endif
