/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_envbis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:33:41 by danelsalome       #+#    #+#             */
/*   Updated: 2023/05/11 15:33:05 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_varenv(char *varenv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (varenv[i] != '=')
		i++;
	while (varenv[i])
	{
		count++;
		i++;
	}
	printf("len = %d\n", count - 1);
	return (count - 1);
}

// calcul len with env
// Si arg[i] == '$' -> regarder si arg[i] == env[i] && sq_closed
// Si non renvoyer 0 et le i initial
// Si oui, renvoyer la len de la variable d'environnement et le i de fin

int len_env(char *arg, t_data *data, int *i, int *sq_open)
{
    int j;
    int k;

    j = 0;
    k = 0;
    if (arg[*i] != '$' || *sq_open != 0)
        return (data->count);
    else
    {
        while (data->new_env[j])
        {
            while (data->new_env[j][k] == arg[*i + 1])
            {
                k++;
                *i = *i + 1;
            }
            if (data->new_env[j][k] == '=' && (arg[*i + 1] == '\0' || arg[*i + 1] == '\''|| arg[*i + 1] == '"'))
                    return (len_varenv(data->new_env[j]) + data->count); // soustraire le nb de char post $
            k = 0;
            j++;
        }
    }
    return (data->count);
}
