/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:22:28 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/02/19 08:13:51 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	if (len >= 1)
		ft_strlcpy(ptr, &s[start], len + 1);
	ptr[len] = 0;
	return (ptr);
}

// int	main(void)
// {
// 	char	str[] = "Copies a part of this string";
// 	char	*ptr;

// 	ptr = ft_substr(str, 9, 4);
// 	printf("print substr: %s", ptr);
// 	if (ptr)
// 		free(ptr);
// 	return (0);
// }
