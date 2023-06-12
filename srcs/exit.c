/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:54:12 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/31 22:53:06 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	exit_msg(char *str, int err)
{
	ft_putendl_fd("exit", 2);
	if (err == 0)
		return ;
	if (err == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("numeric argument required", 2);
	}
	if (err == 2)
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	return ;
}

int	check_exit(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '-' && str[i] != '+')
			return (1);
		if ((str[i] == '-' || str[i] == '+') && i != 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_multiarg(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		if (tab[i][0] != '-'
			&& ft_uatoll(tab[i]) > (unsigned long long)9223372036854775807)
			return (1);
		if (tab[i][0] == '-'
			&& ft_uatoll(tab[i]) > (unsigned long long)9223372036854775807 + 1)
			return (1);
		i++;
	}
	if (i > 2)
		return (2);
	return (0);
}

int	handle_exitcode(int nb, int err, t_data *data)
{
	err = check_exit(data->cmd_tab[1]);
	if (err != 1)
		err = check_multiarg(data->cmd_tab);
	exit_msg(data->cmd_tab[1], err);
	if (err == 2)
	{
		g_exit_code = 1;
		return (0);
	}
	if (err == 1)
		nb = 2;
	else if (data->cmd_tab[1] != NULL)
	{
		nb = ft_uatoll(data->cmd_tab[1]);
		if (data->cmd_tab[1][0] == '-')
			nb = nb * -1;
		nb = nb % 256;
	}
	return (nb);
}

int	mini_exit(t_data *data)
{
	int					err;
	unsigned long long	nb;

	nb = 0;
	err = 0;
	nb = handle_exitcode(nb, err, data);
	// freetab(data->f_arg);
	freetab(data->p_arg);
	freetab(data->new_env);
	freetab(data->prev_env);
	freetab(data->cmd_tab);
	freetab(data->path);
	freetab(data->tmp_arg);
	freetab(data->redir);
	free(data->type);
	free(data->ast);
	close(data->in);
	close(data->out);
	exit(nb);
}
