/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 08:31:25 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/03 08:31:26 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptr2;
	size_t			i;

	i = 0;
	ptr = (unsigned char *) s1;
	ptr2 = (unsigned char *) s2;
	while (i < n)
	{
		if (ptr[i] != ptr2[i])
			return (ptr[i] - ptr2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	str1[] = "Hello Worlda";
// 	char	str2[] = "Hello World";
// 	char	*ptr;
// 	char	*ptr2;

// 	ptr = str1;
// 	ptr2 = str2;
// 	printf("my function: %d\n", ft_memcmp(ptr, ptr2, 12));
// 	printf("real function: %d", memcmp(ptr, ptr2, 12));
// 	return (0);
// }
