/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:14:05 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/26 10:11:00 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_metachar(char *prompt, int count, int i)
{
	if (prompt == NULL)
		return (0);
	while (prompt[++i])
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
		if (j == ft_strlen(prompt) + count_metachar(prompt, count, k))
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
	new_prompt = malloc(sizeof(char) * (ft_strlen(prompt)
				+ count_metachar(prompt, count, j)) + 1);
	if (new_prompt == NULL)
		return (NULL);
	i = add_space(prompt, new_prompt, j);
	new_prompt[i] = '\0';
	free(prompt);
	return (new_prompt);
}

int	split_space(t_data *data, int i)
{
	int	j;

	j = 0;
	data->arg = ft_split(data->clean_prompt, 32);
	while (data->arg[++i])
	{
		while (data->arg[i][j])
		{
			if (data->arg[i][j] == '"' || data->arg[i][j] == '\'')
			{
				while (data->arg[i][j])
				{
					if (data->arg[i][j] == 31)
						data->arg[i][j] = 32;
					j++;
				}
			}
			if (j < ft_strlen(data->arg[i]))
				j++;
		}
		j = 0;
	}
	return (0);
}

void	split_input(char *prompt, t_data *data)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = -1;
	count = 0;
	data->clean_prompt = clean_prompt(prompt);
	data->clean_prompt = handle_quotes(data, i);;
	if (data->clean_prompt == NULL || ft_strlen(data->clean_prompt) == 0)
		return ;
	if (split_space(data, i) == -1)
		return ;
	final_arg(data);
	syntax_error(data);
	split_pipe(data);
	exec(data);
	return ;
}
