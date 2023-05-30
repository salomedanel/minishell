/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:14:05 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/30 23:57:59 by sdanel           ###   ########.fr       */
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

	i = 0;
	j = 0;
	count = 0;
	if (prompt == NULL)
		return (0);
	while (prompt[i])
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
		i++;
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
	printf("i = %d\n", i);
	new_prompt[i] = '\0';
	free(prompt);
	return (new_prompt);
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
	data->clean_prompt = clean_prompt(prompt);
	//printf("clean_prompt1 = %s\n", data->clean_prompt);
	if (ft_strlen(data->clean_prompt) == 0)
	{
		free(data->clean_prompt);
		return ;
	}
	data->clean_prompt = handle_quotes(data, i, &quotes);
	if (data->clean_prompt == NULL || ft_strlen(data->clean_prompt) == 0)
		return ;
	//printf("clean_prompt1 = %s\n", data->clean_prompt);
	if (err_special(data) == 0)
		return ;
	//printf("clean_prompt = %s\n", data->clean_prompt);
	data->arg = ft_split(data->clean_prompt, 32);
	final_arg(data, &quotes);
	if (syntax_err(data) == 0)
		return ;
	if (g_exit_code > 0)
		g_exit_code = 0;
	split_pipe(data, i, j);
	exec(data, i, j);
	return ;
}
