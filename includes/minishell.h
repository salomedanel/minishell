/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danelsalome <danelsalome@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:15:25 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/20 11:53:28 by danelsalome      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define QUOTE_ERR "minishell: syntax error near unexpected token"

typedef enum e_token_type
{
	T_REDIN,
	T_REDOUT,
	T_DREDIN,
	T_LIMITER,
	T_DREDOUT,
	T_WORD,
	T_CMD,
	T_PIPE,
	T_FD
}			t_token_type;

typedef struct s_data
{
	char	*clean_prompt;
	char	**arg;
	char	**f_arg;
	char	**new_env;
	char	**ast;
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
char 		**final_arg(t_data *data);

// parsing_utils00
int			is_metachar(char c);
int			cpy_prompt(char *prompt, char *new_prompt, int j, int i);
int			count_dquotes(char *arg);
int			count_squotes(char *arg);
void		print_arg(char **arg);

// parsing_utils01
void		trim_squotes(char *arg, t_data *data, int index);
void		trim_dquotes(char *arg, t_data *data, int index);
void    	ft_strcpy(char *dest, char *src, int start);

// pars_err
void		quote_err(t_data *data, char *err, char quote);
void		quote_err2(t_data *data, char *err, char quote);

// var_env
void		dup_env(t_data *data, char **env);
int			len_varenv(char *varenv);
int			strncmp_dollar(const char *s1, const char *s2, size_t n);
int			check_varenv(t_data *data, char *arg);
void		replace_dollar(char *arg, t_data *data, int index);

// builtins
// void		mini_echo_loop(t_mini *test, int i);
// int			mini_echo(t_mini *test);
// int			mini_pwd(void);

#endif
