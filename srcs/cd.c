/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:29:32 by tmichel-          #+#    #+#             */
/*   Updated: 2023/06/12 17:56:27 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	set_old_pwd(t_data *data)
{
	int		i;
	char	*tmp;
	char	*pwd_tmp;

	i = -1;
	while (data->new_env[++i])
		if (!ft_strncmp(data->new_env[i], "PWD=", 4))
			pwd_tmp = ft_strdup(data->new_env[i] + 4);
	i = -1;
	while (data->new_env[++i])
	{
		if (!ft_strncmp(data->new_env[i], "OLDPWD=", 7))
		{
			tmp = getcwd(NULL, 0);
			if (!tmp)
				err_cd("chdir", 0);
			free(data->new_env[i]);
			data->new_env[i] = ft_strjoin("OLDPWD=", pwd_tmp);
			free(tmp);
			free(pwd_tmp);
			break ;
		}
	}
}

void	set_pwd(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	set_old_pwd(data);
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

int	count_lines(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
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
		if (g_exit_code == 0)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(data->tmp_arg[1], 2);
			ft_putstr_fd(" No such file or directory\n", 2);
			g_exit_code = 1;
		}
	}
}

int	mini_cd(t_data *data, int j)
{
	int		i;
	char	*tmp;

	i = count_lines(data->tmp_arg);
	if (i > 2)
		return (minicd_err());
	if (i == 1 || !ft_strcmp(data->tmp_arg[1], "~"))
	{
		while (data->new_env[++j])
		{
			if (!ft_strncmp(data->new_env[j], "HOME=", 5))
			{
				tmp = ft_strdup(data->new_env[j] + 5);
				chdir(tmp);
				free(tmp);
				set_pwd(data);
				break ;
			}
			if (j == count_lines(data->new_env) - 1)
				return (err_cd("cd", 1), g_exit_code);
		}
	}
	else
		exec_cd(data);
	return (g_exit_code);
}
