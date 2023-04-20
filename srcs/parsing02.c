/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danelsalome <danelsalome@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:14:50 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/20 17:41:52 by danelsalome      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_finalcheck(t_data *data)
{
	int	i;

	i = 0;
	while (data->arg[i])
	{
		if (data->arg[i][0] == '"' && data->arg[i][ft_strlen(data->arg[i])
			- 1] == '\'')
		{
			quote_err2(data, QUOTE_ERR, '"');
			return (1);
		}
		if (data->arg[i][0] == '\'' && data->arg[i][ft_strlen(data->arg[i])
			- 1] == '"')
		{
			quote_err2(data, QUOTE_ERR, '\'');
			return (1);
		}
		i++;
	}
	return (0);
}

int	new_len(char *arg, t_data *data)
{
	int	i;

	i = 0;
	if (arg[0] == '\'')
		return (ft_strlen(arg) - count_squotes(arg));	
	while (arg[i])
	{
		if (arg[i] == '$')
			return (check_varenv(data, &arg[i]));
		i++;
	}
	if (arg[0] == '"')
		return (ft_strlen(arg) - count_dquotes(arg));
	return (ft_strlen(arg));
}

void	new_words(char *arg, t_data *data, int index)
{
	int	i;

	i = 0;
	if (arg[0] == '\'')
	{
		trim_squotes(arg, data, index);
		return ;
	}
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			replace_dollar(arg, data, index);
			return ;
		}
		i++;
	}
	if (arg[0] == '"')
	{
		trim_dquotes(arg, data, index);
		return ;
	}
	ft_strcpy(data->f_arg[index], arg, 0);
	return ;
}

char **final_arg(t_data *data)
{
	int	i;

	i = 0;
	while (data->arg[i])
		i++;
	data->f_arg = malloc(sizeof(char *) * i);
	i = 0;
	while (data->arg[i])
	{
		data->f_arg[i] = malloc(sizeof(char) * new_len(data->arg[i], data));
		new_words(data->arg[i], data, i);
		i++;
	}
	data->f_arg[i] = NULL;
	return (NULL);
} 

	//QUOTES
	// Comptabiliser le nb de quotes du meme type pour les soustraire a strlen
	// Faire un trim des quotes du meme type 
	//VARENV
	// Checker síl y a un $ dans le mot et quíl nést pas dans des ''. Si oui, verifier que la variable dénvironnement existe.
	// Si oui > remplacer le $mot par la valeur derriere le =
	// Si non > remplacer le $mot par un \n
	// REALLOC
	// Compter le nb de mots dans arg et faire malloc f_arg du nb de mot
	// Parcourir tous les mots pour malloc le strlen de chacun
		// Si quotes -> soustraire nb de quotes au malloc
		// Si $ -> malloc de la taille de la variable
		// free arg 