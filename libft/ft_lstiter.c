/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:04:23 by tmichel-          #+#    #+#             */
/*   Updated: 2022/11/20 19:10:46 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*nextelem;

	if (!f || !lst)
		return ;
	while (lst)
	{
		nextelem = lst->next;
		(*f)(lst->content);
		lst = nextelem;
	}
}
