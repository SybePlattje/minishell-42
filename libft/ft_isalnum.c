/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 07:57:45 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/03 07:57:46 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}

// int	main(void)
// {
// 	unsigned char	a;
// 	unsigned char	b;

// 	a = 'o';
// 	b = '@';
// 	printf("my function:\tyes: %d, no: %d\n", ft_isalnum(a), ft_isalnum(b));
// 	printf("real function:\tyes: %d, no: %d", isalnum(a), isalnum(b));
// 	return (0);
// }
