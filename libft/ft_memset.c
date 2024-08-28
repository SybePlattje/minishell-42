/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:52:53 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/04 13:53:02 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

// int	main(void)
// {
// 	char	str[] = "Filling this with characters";
// 	char	str2[] = "Filling this with characters";
// 	char	c;

// 	c = '*';
// 	ft_memset(str, c, 10);
// 	memset(str2, c, 10);
// 	printf("my function:\t %s\n", str);
// 	printf("real function:\t %s\n", str2);
// 	return (0);
// }
