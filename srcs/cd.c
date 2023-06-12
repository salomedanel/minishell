/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:29:32 by tmichel-          #+#    #+#             */
/*   Updated: 2023/06/12 14:54:07 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	set_pwd(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->new_env[i])
	{
		if (!ft_strncmp(data->new_env[i], "PWD=", 4))
		{
			free(data->new_env[i]);
			tmp = getcwd(NULL, 0);
			data->new_env[i] = ft_strjoin("PWD=", tmp);
			free(tmp);
			break ;
		}
		i++;
	}
}

void	set_old_pwd(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->new_env[i])
	{
		if (!ft_strncmp(data->new_env[i], "OLDPWD=", 7))
		{
			free(data->new_env[i]);
			tmp = getcwd(NULL, 0);
			data->new_env[i] = ft_strjoin("OLDPWD=", tmp);
			free(tmp);
			break ;
		}
		i++;
	}
}

int	count_args(t_data *data)
{
	int	i;

	i = 0;
	while (data->tmp_arg[i])
		i++;
	return (i);
}

void	exec_cd(t_data *data)
{
	set_old_pwd(data);
	if (!chdir(data->tmp_arg[1]))
		set_pwd(data);
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(data->tmp_arg[1], 2);
		ft_putstr_fd(" No such file or directory\n", 2);
	}
}

int	mini_cd(t_data *data, int j)
{
	int		i;
	char	*tmp;

	i = count_args(data);
	if (i > 2)
		return (minicd_err());
	if (i == 1)
	{
		while (data->new_env[++j])
		{
			if (!ft_strncmp(data->new_env[j], "HOME=", 5))
			{
				set_old_pwd(data);
				tmp = ft_strdup(data->new_env[j] + 5);
				chdir(tmp);
				free(tmp);
				set_pwd(data);
				break ;
			}
		}
	}
	else
		exec_cd(data);
	return (g_exit_code);
}
