/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils00.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:01:04 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/29 18:40:44 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	dup_tab(char **tab1, char **tab2)
{
	int	i;

	i = -1;
	while (tab1[++i])
		tab2[i] = ft_strdup(tab1[i]);
	tab2[i] = NULL;
}

int	sizetab(char **tab)
{
	int	i;

	i = -1;
	if (!tab[0] || !tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int	parse_var_to_exp(char *var)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (var[++i] && var[i] != '=')
		if (ft_isspecialchar(var[i]) == 1 || ft_isdigit(var[i]) == 1)
			j++;
	if (j > 0)
		return (1);
	i = -1;
	while (var[++i])
		if (var[i] == '=')
			break ;
	if (i == ft_strlen(var))
		return (1);
	return (0);
}

int	count_var_to_exp(t_data *data)
{
	int	i;
	int	count;

	i = -1;
	count = 1;
	while (data->cmd_tab[++i])
	{
		if (parse_var_to_exp(data->cmd_tab[i]) == 0)
			count++;
		else if (parse_var_to_exp(data->cmd_tab[i]) == 1)
			continue ;
	}
	return (count);
}

int	export_exist(t_data *data, char *var)
{
	int	i;
	int	j;

	j = -1;
	while (data->new_env[++j])
	{
		i = 0;
		while (data->new_env[j][i])
		{
			i++;
			if (data->new_env[j][i] == '=')
				break ;
		}
		if (var[i] && ft_strncmp(data->new_env[j], var, i + 1) == 0)
		{
			free(data->new_env[j]);
			data->new_env[j] = ft_strdup(var);
			return (0);
		}
	}
	return (1);
}