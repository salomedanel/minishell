/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:01:04 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/24 15:50:26 by tmichel-         ###   ########.fr       */
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

int	parse_var_to_exp(char *var)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (var[++i] && var[i] != '=')
		if (ft_isspecialchar(var[i]) == 1)
			j++;
	if (j > 0)
		return (1);
	i = -1;
	while (var[++i])
		if (var[i] == '=')
			break ;
	if (i == ft_strlen(var))
		return (2);
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
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(data->cmd_tab[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (g_exit_code = 1);
		}
		else if (parse_var_to_exp(data->cmd_tab[i]) == 2)
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

int	var_to_unset(t_data *data)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*var;

	i = 0;
	j = 0;
	while (data->new_env[i])
		i++;
	while (data->tmp_arg[++j])
	{
		var = ft_strjoin(data->tmp_arg[j], "=");
		len = ft_strlen(var);
		k = -1;
		while (data->new_env[++k])
			if (!ft_strncmp(data->new_env[k], var, len))
				i--;
	}
	return (i);
}

int	check_unset(char **var_to_unset, char *var_to_check)
{
	int	i;
	int	j;
	int	len;
	char *var;

	j = 0;
	i = 0;
	while (var_to_unset[++i])
	{
		var = ft_strjoin(var_to_unset[i], "=");
		len = ft_strlen(var);
		if (!ft_strncmp(var_to_check, var, len))
			j++;
	}
	if (j > 0)
		return (1);
	return (0);
}
