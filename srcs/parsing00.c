/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:14:05 by sdanel            #+#    #+#             */
/*   Updated: 2023/06/13 12:20:35 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	count_metachar(char *prompt, int count, int i)
{
	if (prompt == NULL)
		return (0);
	while (prompt[++i] && prompt[i + 1])
	{
		if (i == 0 && is_metachar(prompt[i]) == 1)
			norm_count_mc(&count, &i);
		if (is_metachar(prompt[i]) == 1 && is_metachar(prompt[i - 1]) == 0
			&& is_metachar(prompt[i + 1]) == 0)
			count = count + 2;
		if (is_metachar(prompt[i]) == 1 && is_metachar(prompt[i - 1]) == 0
			&& is_metachar(prompt[i + 1]) == 2)
			count++;
		if (is_metachar(prompt[i]) == 1 && is_metachar(prompt[i - 1]) == 2
			&& is_metachar(prompt[i + 1]) == 0)
			count++;
		if (is_metachar(prompt[i]) == 1 && is_metachar(prompt[i - 1]) == 0
			&& is_metachar(prompt[i + 1]) == 1)
			count++;
		if (is_metachar(prompt[i]) == 1 && is_metachar(prompt[i - 1]) == 1
			&& is_metachar(prompt[i + 1]) == 0)
			count++;
	}
	return (count);
}

int	add_space(char *prompt, char *new_prompt, int k)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = 0;
	count = 0;
	if (prompt == NULL)
		return (0);
	while (prompt[++i])
	{
		if (is_metachar(prompt[i + 1]) == 1 && is_metachar(prompt[i]) != 2
			&& (prompt[i] != prompt[i + 1]))
			j = cpy_prompt(prompt, new_prompt, j, i);
		else if (is_metachar(prompt[i]) == 1 && is_metachar(prompt[i + 1]) != 2
			&& is_metachar(prompt[i + 1]) != 1)
			j = cpy_prompt(prompt, new_prompt, j, i);
		else
			new_prompt[j] = prompt[i];
		if (j == ft_strlen(prompt) + count_metachar(prompt, count, k)
			|| j > ft_strlen(prompt) + count_metachar(prompt, count, k))
			return (j);
		j++;
	}
	return (j);
}

char	*clean_prompt(char *prompt)
{
	char	*new_prompt;
	int		i;
	int		j;
	int		count;

	count = 0;
	j = -1;
	if (prompt[0] == '\n')
		return (NULL);
	new_prompt = malloc(sizeof(char) * (ft_strlen(prompt)
				+ count_metachar(prompt, count, j)) + 2);
	if (new_prompt == NULL)
		return (NULL);
	i = add_space(prompt, new_prompt, j);
	new_prompt[i] = '\0';
	free(prompt);
	return (new_prompt);
}

int	handle_prompt(char *prompt, t_data *data, t_quotes *quotes, int i)
{
	data->clean_prompt = clean_prompt(prompt);
	if (ft_strlen(data->clean_prompt) == 0)
	{
		g_exit_code = 0;
		free(data->clean_prompt);
		return (0);
	}
	data->clean_prompt = handle_quotes(data, i, quotes);
	if (data->clean_prompt == NULL || ft_strlen(data->clean_prompt) == 0)
		return (0);
	return (1);
}

void	parsing(char *prompt, t_data *data)
{
	int			i;
	int			j;
	t_quotes	quotes;

	i = -1;
	j = 0;
	quotes.dq_open = 0;
	quotes.sq_open = 0;
	if (handle_prompt(prompt, data, &quotes, i) == 0)
		return ;
	if (err_special(data) == 0)
		return ;
	data->arg = ft_split(data->clean_prompt, 32);
	final_arg(data, &quotes);
	if (syntax_err(data, &quotes) == 0)
		return ;
	if (g_exit_code > 0)
		g_exit_code = 0;
	split_pipe(data, i, j);
	here_doc(data);
	exec(data, i);
	signal(SIGQUIT, SIG_IGN);
	return ;
}
