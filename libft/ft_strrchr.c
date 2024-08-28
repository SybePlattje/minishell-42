/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 08:30:45 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/03 08:30:46 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*pnt;
	size_t	i;

	pnt = (char *)s;
	i = 0;
	if (pnt[i] == '\0')
	{
		if (c == 0)
			return (pnt);
		return (0);
	}
	while (pnt[i] != '\0')
		i++;
	while ((int)i > -1)
	{
		if (pnt[i] == (char)c)
			return (pnt + i);
		i--;
	}
	return (0);
}

// int	main(void)
// {
// 	char	str[] = "Search after the last char";
// 	int		a;
// 	char	str2[] = "Search after the last char";

// 	a = 't';
// 	//printf("my function:\t%c\n", ft_strrchr(str, a)[0]);
// 	printf("my funtion:\t%s\n", ft_strrchr(str, a));
// 	//printf("real function\t%c\n", strrchr(str2, a)[0]);
// 	printf("real function:\t%s", strrchr(str2, a));
// 	return (0);
// }
