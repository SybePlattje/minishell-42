/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:56:54 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/16 14:56:56 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		i;

	current = lst;
	i = 0;
	if (lst)
	{
		while (current != NULL)
		{
			current = current->next;
			i++;
		}
	}
	return (i);
}
