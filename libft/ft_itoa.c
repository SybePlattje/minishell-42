/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:26:57 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/06 09:26:58 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

static char	*fill(char *str, int n, int sign)
{
	int	len;

	len = count_digits(n);
	if (sign == 1)
	{
		str[0] = '-';
		len++;
	}
	str[len] = '\0';
	len --;
	while (n > 9)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	str[len] = n + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		num;

	sign = -1;
	if (n == INT_MIN)
		num = 11;
	else
		num = count_digits(n);
	str = (char *)malloc(sizeof(char) * num + 1);
	if (!str)
		return (NULL);
	if (n == INT_MIN)
	{
		ft_strlcpy(str, "-2147483648", 13);
		return (str);
	}
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	return (str = fill(str, n, sign));
}

// int	main(void)
// {
// 	int		numb;
// 	char	*result;

// 	numb = INT_MIN;
// 	result = ft_itoa(numb);
// 	printf("result: %s\n", result);
// 	if (result)
// 		free(result);
// 	return (0);
// }
