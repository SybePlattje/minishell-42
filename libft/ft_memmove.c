/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:54:15 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/04 13:54:17 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*move(unsigned char *dst, unsigned char *sr, size_t n)
{
	size_t	i;

	if (sr < dst)
	{
		i = 1;
		while (i <= n)
		{
			dst[n - i] = sr[n - i];
			i++;
		}
	}
	else
	{
		i = 0;
		while (n > 0)
		{
			dst[i] = sr[i];
			n--;
			i++;
		}
	}
	return (dst);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*sr;

	dst = (unsigned char *)dest;
	sr = (unsigned char *)src;
	if (!dst && !sr)
		return (NULL);
	return (move(dest, sr, n));
}

// int	main(void)
// {
// 	const char	str[] = "newstring12345";
// 	char		dest[] = "old123";
// 	size_t		n;
// 	const char	str2[] = "newstring12345";
// 	char		dest2[] = "old123";
// 	n = 10;
// 	ft_memmove(dest, str, n);
// 	memmove(dest2, str2, n);
// 	printf("new function:\t%s\n", (char *)dest);
// 	printf("real function:\t%s", (char *)dest2);
// 	return (0);
// }
