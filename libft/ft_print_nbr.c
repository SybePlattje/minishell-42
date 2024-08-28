/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_diu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:46:38 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/24 09:46:39 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long int n)
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

static int	ft_itoa_long(unsigned int n)
{
	char	c;
	int		count;

	count = count_digits(n);
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, 1);
		n = n % 10;
	}
	if (n < 10)
	{
		c = n + 48;
		ft_putchar_fd(c, 1);
	}
	return (count);
}

int	print_un_i(unsigned int num, int count)
{
	count += ft_itoa_long(num);
	return (count);
}

int	print_d(int num, int count)
{
	char	*str_num;

	str_num = ft_itoa(num);
	if (!str_num)
		return (0);
	count += write(1, str_num, ft_strlen(str_num));
	free(str_num);
	return (count);
}
