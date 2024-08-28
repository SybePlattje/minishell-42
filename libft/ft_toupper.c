/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 08:30:06 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/03 08:30:08 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}

// int	main(void)
// {
// 	char	a;
// 	char	b;

// 	a = 'h';
// 	b = 'G';
// 	printf("a -> %c, b -> %c", ft_toupper(a), ft_toupper(b));
// 	return (0);
// }
