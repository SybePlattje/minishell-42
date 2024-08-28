/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 08:29:38 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/03 08:29:40 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstl;
	size_t	i;
	size_t	num;

	dstl = ft_strlen(dst);
	i = 0;
	if (size == 0)
	{
		num = ft_strlen(src);
		return (num);
	}
	else if (size < dstl)
		num = ft_strlen(src) + size;
	else
		num = dstl + ft_strlen(src);
	while (src[i] != '\0' && dstl < size - 1)
	{
		dst[dstl] = src[i];
		dstl++;
		i++;
	}
	dst[dstl] = '\0';
	return (num);
}

// int	main(void)
// {
// 	char	src[] = "AAAAAAAAA";
// 	char	dst[] = "";
// 	char	src2[] = "AAAAAAAAA";
// 	char	dst2[] = "";
// 	size_t	len;

// 	len = 1;
// 	printf("my lenght:\t%zu\n", ft_strlcat(dst, src, len));
// 	printf("real lenght:\t%zu\n", strlcat(dst2, src2, len));
// 	printf("my function dst:\t%s\n", dst);
// 	printf("real function dst:\t%s", dst2);
// 	//lbsd
// 	return (0);
// }
