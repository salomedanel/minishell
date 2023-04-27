/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:01:04 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/27 16:26:51 by tmichel-         ###   ########.fr       */
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

// char	*parse_var_to_exp(char *var)
// {
// 	int		i;
// 	int		j;
// 	int		len;
// 	char	*clean;

// 	i = -1;
// 	j = 0;
// 	len = ft_strlen(var);
// 	while (var[++i])
// 		if (ft_isspecialchar(var[j]) == 1)
// 			j++;
// 	clean = malloc(sizeof(char) * (len - j + 1));
// 	if (!clean)
// 		return (NULL);
// 	while (var[++i] != '=')
// 		if (ft_isalnum(var[i] == 0) && ft_isspecialchar(var[i]) == 0)
// 			return (NULL);
// 	i = -1;
// 	j = 0;
// 	while (var[++i])
// 	{
// 		while (ft_isspecialchar(var[i]) == 1)
// 			i++;
// 		clean[j] = var[i];
// 		j++;
// 	}
// 	clean[i] = '\0';
// 	return (clean);
// }

int	var_to_unset(t_data *data)
{
	int	j;
	int	i;

	i = 0;
	j = -1;
	while (data->new_env[i])
		i++;
	while (data->f_arg[++j])
	{
		if (ft_strchr(data->f_arg[j], '='))
		{
			g_exit_code = 1;
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(data->f_arg[j], 2);
			ft_putendl_fd(": invalid parameter name", 2);
			i--;
		}
	}
	return (i);
}
