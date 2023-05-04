/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:01:04 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/04 14:57:04 by tmichel-         ###   ########.fr       */
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

// char	*get_clean_var(char *var)
// {
// 	int	i;
// 	int	j;
// 	int	len;
// 	char	*clean;

// 	i = -1;
// 	j = 0;
// 	len = ft_strlen(var);
// 	while (var[++i] != '=')
// 		if (ft_isspecialchar(var[j]) == 1)
// 			j++;
// 	clean = malloc(sizeof(char) * (len - j + 1));
// 	if (!clean)
// 		return (NULL);
// 	i = 1;
// 	while(var[i] != '=')
// 	{
// 		if (ft_isspecialchar(var[i]) == 1)
// 			i++;
// 		clean[i] = var[i];
// 		i++;
// 	}
// 	clean[i] = '\0';
// 	return (clean);
// }

int	parse_var_to_exp(char *var)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (var[++i] && var[++i] != '=')
		if (ft_isspecialchar(var[i]) == 1)
			j++;
	if (j > 0)
		return (1);
	return (0);
}

int	count_var_to_exp(t_data *data)
{
	int	i;

	i = 0;
	while (data->f_arg[i])
	{
		if (parse_var_to_exp(data->f_arg[i]) == 1)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(data->f_arg[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (g_exit_code = 1);
		}
		i++;
	}
	return (i);
}

int	export_exist(t_data *data, char *var)
{
	int	i;
	int	j;

	j = -1;
	while (data->new_env[++j])
	{
		i = 0;
		while (data->new_env[j][i] && data->new_env[j][i] != '=')
			i++;
		if (var[i] && ft_strncmp(data->new_env[j], var, i) == 0)
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
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	j = 0;
	while (data->new_env[i])
		i++;
	while (data->f_arg[++j])
	{
		len = ft_strlen(data->f_arg[j]);
		k = -1;
		while (data->new_env[++k])
			if (!ft_strncmp(data->new_env[k], data->f_arg[j], len))
				i--;
	}
	return (i);
}

int	check_unset(char **var_to_unset, char *var_to_check)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 0;
	len = 0;
	while (var_to_check[++i] && var_to_check[i] != '=')
		len++;
	i = -1;
	while (var_to_unset[++i])
	{
		if (!ft_strncmp(var_to_unset[i], var_to_check, len))
			j++;
	}
	if (j == 0)
		return (1);
	return (0);
}
