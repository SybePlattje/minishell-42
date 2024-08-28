/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_save.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:31:53 by splattje          #+#    #+#             */
/*   Updated: 2024/03/12 13:18:30 by mvan-ess         ###   ########.fr       */
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
 * @param const_char *nptr: the string being converted.
 * @param long_int *number: the converted number.
 * @brief a atoi that checks on overflow and change number.
 * @return retuns 0 if overflow happened, 1 if not.
*/
int	ft_atoi_save(const char *nptr, long int *number)
{
	int			i;
	int			sign;
	long int	*num;

	num = number;
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
		*num = *num * 10 + (nptr[i++] - 48);
		if (*num < (*num / 10))
			return (0);
	}
	*num = *num * sign;
	return (1);
}
