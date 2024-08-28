/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 08:28:53 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/03 08:28:55 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*sr;
	unsigned char	*dst;
	size_t			i;

	i = 0;
	dst = (unsigned char *)dest;
	sr = (unsigned char *)src;
	if (!dst && !sr)
		return (NULL);
	while (i < n)
	{
		dst[i] = sr[i];
		i++;
	}
	return (dst);
}

// int	main(void)
// {
// 	char	str[] = "A";
// 	char	ptr[2];
// 	char	str2[] = "A";
// 	char	ptr2[2];
// 	int		len;

// 	len = 2;
// 	ft_memcpy(&ptr, str, len);
// 	printf("my function: %s\n", ptr);
// 	ft_memcpy(&ptr2, str2, len);
// 	printf("real function: %s", ptr2);
// 	return (0);
// }
