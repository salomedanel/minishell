/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:15:25 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/12 16:41:11 by sdanel           ###   ########.fr       */
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
	char	*new_prompt;
	char	**arg;
}			t_data;

// parsing00
int			is_metachar(char c);
int			count_metachar(char *prompt);
int			add_space(char *prompt, char *new_prompt);
char		*clean_prompt(char *prompt);
void		split_input(char *prompt);

// parsing01
int			odd_dquotes(t_data *data);
int			odd_squotes(t_data *data);
void		space_dquotes(t_data *data);

// builtins
void		mini_echo_loop(t_mini *test, int i);
int			mini_echo(t_mini *test);
int			mini_pwd(void);

#endif
