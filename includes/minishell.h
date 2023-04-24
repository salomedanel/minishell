/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:15:25 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/24 15:32:27 by sdanel           ###   ########.fr       */
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
# include <unistd.h>

# define QUOTE_ERR "minishell: syntax error near unexpected token"

typedef enum e_token_type
{
	T_PIPE,           // 0 |
	T_REDOUT,         // 1 >
	T_REDIN,          // 2 <
	T_HERE_DOC,       // 3 <<
	T_RED_OUT_APPEND, // 4 >>
	T_OUTFILE_TRUNC,  // 5 > word + 1
	T_INFILE,         // 6
	T_LIMITER,        // 7 << word + 1
	T_OUTFILE_APPEND, // 8
	T_CMD,            // 9
	T_OPTION,         // 10
	T_WORD,           // 11
	T_BUILTIN		 // 12
}			t_token_type;

typedef struct s_data
{
	char	*clean_prompt;
	char	**arg;
	char	**f_arg;
	char	**new_env;
	int		*ast;
}			t_data;

// parsing00
int			count_metachar(char *prompt);
int			add_space(char *prompt, char *new_prompt);
char		*clean_prompt(char *prompt);
void		split_input(char *prompt, char **env);

// parsing01
int			check_otherquote(char *prompt, int i, int quote);
int			space_dquotes(t_data *data);
int			space_squotes(t_data *data);
char		*handle_quotes(t_data *data, int i);
void		split_space(t_data *data, int i);

// parsing02
int			quote_finalcheck(t_data *data);
int			new_len(char *arg, t_data *data);
void		new_words(char *arg, t_data *data, int index);
void		final_arg(t_data *data);

// parsing_utils00
int			is_metachar(char c);
int			cpy_prompt(char *prompt, char *new_prompt, int j, int i);
int			count_dquotes(char *arg);
int			count_squotes(char *arg);
void		print_arg(char **arg);

// parsing_utils01
void		trim_squotes(char *arg, t_data *data, int index);
void		trim_dquotes(char *arg, t_data *data, int index);
void		ft_strcpy(char *dest, char *src, int start);

// pars_err
void		quote_err(t_data *data, char *err, char quote);
void		quote_err2(t_data *data, char *err, char quote);
void		metachar_err(t_data *data, char *err, char *metachar);

// var_env
void		dup_env(t_data *data, char **env);
int			len_varenv(char *varenv);
int			strncmp_dollar(char *env, char *arg);
int			check_varenv(t_data *data, char *arg);
void		replace_dollar(char *arg, t_data *data, int index);

// token
void		token(t_data *data);
void		print_arg_ast(t_data *data);
int			init_ast(t_data *data);
int			token_metachar(t_data *data);
int			token_word_metachar(t_data *data, int nb_arg);
int			token_command_option(t_data *data);

// signal
void		handle_sigint(int sig);

// free
void		free_arg(t_data *data);
void		free_parsing_token(t_data *data);

// builtins
int			is_builtin(char *str);
int			exec_builtin(char **envp, t_data *data);
void		mini_echo_loop(t_data *data, int i);
int			mini_echo(t_data *data);
int			mini_pwd(void);

// builtins_revenge
int			mini_cd(t_data *data);

// env
int			mini_env(t_data *data);
int			mini_export(char **envp, t_data *data);
int			mini_unset(char **envp, t_data *data);

#endif
