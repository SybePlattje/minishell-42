/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 07:57:15 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/03 07:57:17 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

// int	main(void)
// {
// 	char	a;
// 	char	b;

// 	a = '5';
// 	b = 'b';
// 	printf("my function:\tdigit: %d, not: %d\n", ft_isdigit(a), ft_isdigit(b));
// 	printf("real function:\tdigit: %d, not: %d", isdigit(a), isdigit(b));
// 	return (0);
// }
