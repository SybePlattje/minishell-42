/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 08:31:13 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/03 08:31:14 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	ch;

	ch = c;
	if (!s)
		return (NULL);
	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (*ptr == ch)
			return (ptr);
		ptr++;
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	str[] = "Hello World";
// 	char	*src;
// 	int		c;

// 	c = 'o';
// 	src = ft_memchr(str, c, 12);
// 	printf("my function: %c\n", *src);
// 	src = memchr(str, c, 12);
// 	printf("real function: %c\n", *src);
// 	return (0);
// }
