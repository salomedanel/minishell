/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:15:25 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/17 14:06:12 by sdanel           ###   ########.fr       */
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

int exit_code = 0;

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

typedef struct s_mini
{
	char	**full_cmd;
	char	**full_path;
	char	**ast;
	int		infile;
	int		outfile;
}			t_mini;

typedef struct s_data
{
	char	*clean_prompt;
	char	*final_prompt;
	char	**arg;
}			t_data;

// parsing00
int			is_metachar(char c);
int			count_metachar(char *prompt);
int			add_space(char *prompt, char *new_prompt);
char		*clean_prompt(char *prompt);
void		split_input(char *prompt);

// parsing01
int			check_otherquote(char *prompt, int i, int quote);
int			space_dquotes(t_data *data);
int			space_squotes(t_data *data);
char		*handle_quotes(t_data *data);
void		split_space(t_data *data);

// parsing_utils
int			is_metachar(char c);
int			cpy_prompt(char *prompt, char *new_prompt, int j, int i);

// builtins
void		mini_echo_loop(t_mini *test, int i);
int			mini_echo(t_mini *test);
int			mini_pwd(void);

#endif
