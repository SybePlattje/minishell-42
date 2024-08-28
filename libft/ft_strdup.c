/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:23:46 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/03 09:23:47 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*pnt;
	size_t	len;

	len = ft_strlen(s);
	pnt = malloc(sizeof(char) * len + 1);
	if (!pnt)
		return (NULL);
	ft_strlcpy(pnt, s, len + 1);
	return (pnt);
}

// int	main(void)
// {
// 	char	string[] = "Making a new string";
// 	char	*ptr;
// 	char	string2[] = "Making a new string";
// 	char	*ptr2;

// 	ptr = ft_strdup(string);
// 	printf("my function:\t%s\n", ptr);
// 	ptr2 = strdup(string);
// 	printf("real function:\t%s", ptr2);
// 	if (ptr)
// 		free(ptr);
// 	if (ptr2)
// 		free(ptr2);
// 	return (0);
// }
