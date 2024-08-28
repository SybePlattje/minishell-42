/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:43:31 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/24 09:43:33 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_h_len(unsigned long num)
{
	int	i;

	i = 0;
	while (num > 0)
	{
		num /= 16;
		i++;
	}
	return (i);
}

static void	to_hex(unsigned long num, char *str, int h_len, char sort)
{
	char	c;
	int		i;

	str[h_len] = '\0';
	i = h_len - 1;
	while (i >= 0)
	{
		if (num % 16 < 10)
		{
			c = num % 16 + '0';
			str[i] = c;
		}
		else
		{
			if (sort == 'X')
				c = num % 16 - 10 + 'A';
			else
				c = num % 16 - 10 + 'a';
			str[i] = c;
		}
		num /= 16;
		i--;
	}
}

int	print_hex(unsigned long num, int count, char sort)
{
	char	*str;
	int		h_len;

	if (num == 0 && sort == 'p')
		return (count += write(1, "(nil)", 5));
	if (num == 0)
		return (count += write(1, "0", 1));
	h_len = count_h_len(num);
	str = (char *)malloc(sizeof(char) * h_len + 1);
	if (!str)
		return (0);
	to_hex(num, str, h_len, sort);
	if (sort == 'p')
		count += write(1, "0x", 2);
	count += write(1, str, ft_strlen(str));
	free(str);
	return (count);
}
