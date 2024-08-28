/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 08:30:58 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/13 07:56:37 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	return (0);
}

// int	main(void)
// {
// 	size_t	size;
// 	char	string1[] = "123\0123";
// 	char	string2[] = "123\234";

// 	size = 4;
// 	printf("my function:\t%d\n", ft_strncmp(string1, string2, size));
// 	printf("real function:\t%d", strncmp(string1, string2, size));
// 	return (0);
// }
