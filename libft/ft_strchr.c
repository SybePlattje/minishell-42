/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 08:30:28 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/03 08:30:30 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = (char)c;
	while (*s)
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (*s == ch)
		return ((char *)s + ft_strlen(s));
	else
		return (0);
}

// int	main(void)
// {
// 	char	str[] = "Searching for the first character";
// 	int		c;

// 	c = 'f';
// 	printf("my function:\t%s\n", ft_strchr(str, c));
// 	printf("real function:\t%s", strchr(str, c));
// 	return (0);
// }
