/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:49:30 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/06 11:49:32 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	f(unsigned int x, char *c)
// {
// 	if (x % 2 == 1)
// 		c[x] = '*';
// }

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// int	main(void)
// {
// 	char	str[] = "0000000000";

// 	ft_striteri(str, f);
// 	printf("%s", str);
// 	return (0);
// }
