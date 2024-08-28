/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 08:29:22 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/03 08:29:23 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size <= 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

// int	main(void)
// {
// 	char	src[] = "Hello";
// 	char	dst[10];
// 	char	src2[] = "Hello";
// 	char	dst2[10];
// 	size_t	len;
// 	int		l;

// 	len = -1;
// 	l = ft_strlcpy(dst, src, len);
// 	//l = strlcpy(dst, src, len);
// 	printf("my function:\tString: %s\tLength: %d\n", dst, l); // lbsd
// 	l = strlcpy(dst2, src2, len);
// 	printf("real function:\tString: %s\tLength: %d\n", dst2, l);
// 	return (0);
// }
