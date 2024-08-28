/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_letters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:45:22 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/24 09:45:24 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_str(char *str, int count)
{
	if (!str)
	{
		count += write(1, "(null)", 6);
		return (count);
	}
	count += write(1, str, ft_strlen(str));
	return (count);
}

int	print_char(char c, int count)
{
	count += write(1, &c, 1);
	return (count);
}
