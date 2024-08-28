/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:51:33 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/03 11:51:34 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((int)nmemb < 0 || (int)size < 0)
		return (NULL);
	if ((int)nmemb > 0 || (int)size > 0)
	{
		if ((nmemb * size) / nmemb != size)
			return (NULL);
	}
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size * nmemb);
	return (ptr);
}

// int	main(void)
// {
// 	char	*ptr;
// 	char	str[] = "Hello";
// 	char	*ptr2;
// 	char	str2[] = "Hello";
// 	size_t	nmemb;
// 	size_t	size;

// 	nmemb = 0;
// 	size = 0;
// 	ptr = ft_calloc(nmemb, size);
// 	if (ptr == NULL)
// 		write(1, "error", 5);
// 	ft_strlcpy(ptr, str, 6);
// 	printf("my function:\tfirst: %s \nafter: %s\n", str, ptr);
// 	ptr2 = ft_calloc(nmemb, size);
// 	if (ptr2 == NULL)
// 		write(1, "error", 5);
// 	ft_strlcpy(ptr2, str2, 6);
// 	printf("real function:\tfirst: %s \nafter: %s", str, ptr);
// 	if (ptr)
// 		free(ptr);
// 	if (ptr2)
// 	free(ptr2);
// 	return (0);
// }
