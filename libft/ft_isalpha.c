/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:40:39 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/02 14:53:15 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

// int	main(void)
// {
// 	unsigned char	a;
// 	unsigned char	b;

// 	a = '1';
// 	b = 'a';
// 	printf("my function:\ta = %d & b = %d\n", ft_isalpha(a), ft_isalpha(b));
// 	printf("real function:\ta = %d & b = %d", isalpha(a), isalpha(b));
// 	return (0);
// }
