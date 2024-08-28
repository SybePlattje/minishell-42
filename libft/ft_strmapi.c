/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:06:44 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/06 11:06:45 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	f(unsigned int n, char c)
// {
// 	if (c >= 'a' && c <= 'z' && n < 10)
// 		return (c);
// 	else
// 		return ('*');
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;
	size_t	len;

	i = 0;
	if (ft_strlen(s) < 1)
		len = 0;
	else
		len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}

// int	main(void)
// {
// 	char	str[] = "Change this str";
// 	char	*ptr;

// 	ptr = ft_strmapi(str, f);
// 	printf("%s \n", ptr);
// 	if (ptr)
// 		free(ptr);
// 	return (0);
// }
