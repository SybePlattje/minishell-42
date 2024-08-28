/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:57:49 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/04 13:57:50 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*searching(size_t len, char *pnt, size_t l, char *little)
{
	size_t	i;
	size_t	j;
	size_t	l_copy;

	i = 0;
	l_copy = l;
	while (i < len && pnt[i] != '\0')
	{
		j = 0;
		if (pnt[i] == little[j])
		{
			while (pnt[i + j] == little[j] && i + j < len)
			{
				l--;
				if (l == 0)
					return (&pnt[i]);
				j++;
			}
			j = 0;
			l = l_copy;
		}
		i++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_l;
	char	*hay;
	char	*lit;

	lit = (char *)little;
	hay = (char *)big;
	len_l = ft_strlen(lit);
	if (len == 0 && little[0] == '\0')
		return (hay);
	if (len == 0)
		return (NULL);
	if (!lit || lit[0] == 0 || len < len_l)
		return (hay);
	return (searching(len, hay, len_l, lit));
}

// int	main(void)
// {
// 	char	str[] = "search in this string";
// 	char	search[] = "a";

// 	printf("my function: %s\n", ft_strnstr(str, search, 5));
// 	printf("real function: %s", strnstr(str, search, 5));
// 	return (0);
// }
