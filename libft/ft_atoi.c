/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 08:31:51 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/12 13:20:00 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		&& str[i] != '\0')
		i++;
	return (i);
}

/**
 * @param const_char *nptr: the string being converted
 * @brief converts the initial portion of the string pointed to by nptr to int.
 * @return the converted value or 0 on error.
*/
int	ft_atoi(const char *nptr)
{
	long int	num;
	int			i;
	int			sign;

	num = 0;
	sign = 1;
	i = 0;
	if ((nptr[0] >= 9 && nptr[0] <= 13) || nptr[0] == ' '
		|| nptr[0] == '+')
		i = ft_whitespace(nptr);
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] != '\0' && ft_isdigit(nptr[i]))
	{
		num += (nptr[i++] - 48);
		num *= 10;
	}
	return (sign * (num /= 10));
}

// int	main(void)
// {
// 	char	nmb[] = "     -2.46";
// 	int		nm;

// 	nm = ft_atoi(nmb);
// 	printf("my function:\t%d\n", nm);
// 	printf("real function:\t%d", atoi(nmb));
// 	return (0);
// }
