/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 07:58:07 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/03 07:58:08 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c < 127);
}

// int	main(void)
// {
// 	unsigned char	a;
// 	wchar_t			b;

// 	a = 'e';
// 	b = '~' + 1;
// 	printf("my function:\te: %d, €: %d\n", ft_isprint(a), ft_isprint(b));
// 	printf("real function:\te: %d, €: %d", isprint(a), isprint(b));
// 	return (0);
// }
