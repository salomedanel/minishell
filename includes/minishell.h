/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:15:25 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/26 16:02:22 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define ERR_MSG "minishell: syntax error near unexpected token"
# define ERR_MSG_NL "minishell: syntax error near unexpected token 'newline'"

typedef enum e_token_type
{
	T_PIPE,           // 0
	T_REDOUT,         // 1 >
	T_REDIN,          // 2 <
	T_HERE_DOC,       // 3 <<
	T_RED_APPEND,     // 4 >>
	T_OUTFILE_TRUNC,  // 5 > word + 1
	T_INFILE,         // 6
	T_LIMITER,        // 7 << word + 1
	T_OUTFILE_APPEND, // 8
	T_CMD,            // 9
	T_OPTION,         // 10
	T_BUILTIN         // 11
}			t_token_type;

typedef struct s_data
{
	char	*clean_prompt;
	char	*tmp_prompt;
	char	**arg;
	char	**f_arg;
	char	**p_arg;
	char	**tmp_arg;
	char	**new_env;
	char	**prev_env;
	char	**cmd_tab;
	char	**path;
	int		*ast;
	int		count;
	int		count_cmd;
	int		cmd_id;
	int		prev_pipe;
	int		fd[2];
	int		pid[1024];
	int		act_fd;
	int		in;
	int		out;
	char	**redir;
	int		*type;
}			t_data;

typedef struct s_quotes
{
	int		dq_open;
	int		sq_open;
	char	*arg;
	int		index;
	int		counter;
	char	*tmp;
}			t_quotes;

// parsing00
int			count_metachar(char *prompt, int count, int i);
int			add_space(char *prompt, char *new_prompt, int k);
char		*clean_prompt(char *prompt);
int			split_space(t_data *data, int i);
void		parsing(char *prompt, t_data *data);

// handle_quotes
int			check_quotes_open(int dquotes, int squotes);
void		replace_space(t_data *data, int *dq_open, int *sq_open, int i);
char		*handle_quotes(t_data *data, int i);
int			count_newlen(t_data *data, t_quotes *quotes);
void		trimquotes(t_data *data, t_quotes *quotes, int i, int j);

// parsing01
int			new_len(char *arg, t_data *data, t_quotes *quotes);
void		new_words(char *arg, t_data *data, int index, t_quotes *quotes);
void		final_arg(t_data *data);

// parsing_utils00
int			is_metachar(char c);
int			cpy_prompt(char *prompt, char *new_prompt, int j, int i);
int			open_quotes(char c, t_quotes *quotes, int *i, int *count);
int			close_quotes(char c, t_quotes *quotes, int *count);
int			count_char(char *arg, char c);

// parsing_utils01
void		trquotes_util1(char c, int *dq_open, int *sq_open, int *i);
void		trquotes_util2(char c, int *dq_open, int *sq_open, int *i);
int			cpy_varenv(t_data *data, t_quotes *quotes, int *i, int *j);
void		ft_strcpy(char *dest, char *src, int start);
void		norm_count_mc(int *count, int *i);

// pars_error;
void		err_msg(char *err, char quote);
void		err_msg_newline(char *err);
int			syntax_error(t_data *data);
int			sing_syntax_error(t_data *data);
int			mult_syntax_error(t_data *data);

// parserr_utils
int			metachar_type(char c);
int			count_metac(char *str);
int			str_contains_mc(char *str);
int			tab_len(char **tab);

// var_env
void		dup_env(t_data *data, char **env);
int			varenv_len(t_quotes *quotes, t_data *data, int *i);
char		*replace_dollar(t_quotes *quotes, int *i, t_data *data);
char		*replace_dollar_utils(t_quotes *quotes, int *tmp_i, int *i,
				t_data *data);
char		*ft_getenv(t_data *data, char *varname);
char		*get_dollvalue(t_quotes *quotes, int *tmp_i, int *i);

// quotes_env_utils
int			trimquotes_utils(t_quotes *quotes, int *count);
char		*ft_getenv(t_data *data, char *varname);

// token
void		token(t_data *data);
int			token_metachar(t_data *data);
int			token_word_metachar(t_data *data, int nb_arg);
int			token_command_option(t_data *data);
int			init_ast(t_data *data);

// temporary_utils
void		print_arg(char **arg);
void		print_arg_ast(t_data *data);

// signal
void		handle_sigint(int sig);
void		handle_sigquit(int sig);

// free
void		free_arg(t_data *data);
void		freefrom_quotes_err(t_data *data);
void		freefrom_syntax_err(t_data *data);
int			mini_exit(t_data *data);
int			freetab(char **tab);
void		free_dobby(t_data *data);
int			mini_exit_bis(t_data *data);

// builtins
int			is_builtin(char *str);
int			unforkable_builtins(char *str);
int			exec_builtin(t_data *data, char *builtin);
void		mini_echo_loop(t_data *data, int i);
int			mini_echo(t_data *data);
int			mini_pwd(void);

// cd
void		set_pwd(t_data *data);
void		set_old_pwd(t_data *data);
int			count_args(t_data *data);
void		exec_cd(t_data *data);
int			mini_cd(t_data *data);

// env
int			mini_env(t_data *data);
int			mini_export(t_data *data);
int			mini_unset(t_data *data);

//env_utils
void		dup_tab(char **tab1, char **tab2);
int			parse_var_to_exp(char *var);
int			count_var_to_exp(t_data *data);
int			export_exist(t_data *data, char *var);
int			var_to_unset(t_data *data);
int			check_unset(char **var_to_unset, char *var_to_check);
//pipex_utils00
int			count_cmd(t_data *data);
int			count_sub_cmd(t_data *data);
char		*ft_jointab(char **tab);
void		cmd_not_found(char *cmd);
void		dupnclose(int fd1, int fd2);

// pipex_utils01
void		get_cmd_tab(t_data *data);
char		**ft_get_path(t_data *data);
char		*get_cmd_path(char *cmd, char **path);
void		ft_op_error(char *str);
int			count_redir_out(t_data *data);
int			open_files(t_data *data);

// pipex_newbis
void		select_pipe(t_data *data, int i);
void		exec(t_data *data);

// split pipe
char		*ft_jointab(char **tab);
void		ft_strcpy_pipe(char *dest, char *src, int count);
char		**split_pipe(t_data *data);

#endif
