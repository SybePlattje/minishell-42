/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 07:57:55 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/03 07:57:57 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

// int	main(void)
// {
// 	unsigned char	a;
// 	wchar_t			b;

// 	a = 'g';
// 	b = L'¥';
// 	printf("my function:\tascii: %d, not: %d\n", ft_isascii(a), ft_isascii(b));
// 	printf("real function:\tascii: %d, not: %d", isascii(a), isascii(b));
// 	return (0);
// }
