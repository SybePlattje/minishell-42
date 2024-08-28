/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:44:32 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/15 13:44:33 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list) * 1);
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// int	main(void)
// {
// 	t_list	*newNode;

// 	newNode = ft_lstnew("Test this new node");
// 	if (!newNode)
// 		printf("Error");
// 	else
// 		printf("New node");
// 	free(newNode);
// 	return (0);
// }