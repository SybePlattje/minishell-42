/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:07:17 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/05 11:07:18 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		strl_1;
	int		strl_2;

	if (!s1 || !s2)
		return (NULL);
	strl_1 = ft_strlen(s1);
	strl_2 = ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (strl_1 + strl_2 + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, strl_1 + 1);
	ft_strlcat(ptr, s2, strl_2 + strl_1 + 1);
	return (ptr);
}

// int	main(void)
// {
// 	char	str[] = "Stick ";
// 	char	str2[] = "Together";
// 	char	*ptr;

// 	ptr = ft_strjoin(str, str2);
// 	printf("%s", ptr);
// 	if (ptr)
// 		free(ptr);
// 	return (0);
// }
