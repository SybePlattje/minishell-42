/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 07:27:26 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/23 07:27:27 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_flag(char *input, int i)
{
	char	c;

	c = input[i];
	if (c == '.' || c == '-' || c == ' ' || c == '#'
		|| c == '+' || ft_isdigit(c))
		return (1);
	else
		return (0);
}

static int	check_conversion(char *input, int i, va_list ap, int count)
{
	while (skip_flag(input, i) && input[i] != '\0')
		i++;
	if (input[i] == 'd' || input[i] == 'i')
		count = print_d(va_arg(ap, int), count);
	else if (input[i] == 'c')
		count = print_char(va_arg(ap, int), count);
	else if (input[i] == 's')
		count = print_str(va_arg(ap, char *), count);
	else if (input[i] == 'p')
		count = print_hex(va_arg(ap, unsigned long), count, input[i]);
	else if (input[i] == 'x' || input[i] == 'X')
		count = print_hex(va_arg(ap, unsigned int), count, input[i]);
	else if (input[i] == 'u')
		count = print_un_i(va_arg(ap, unsigned int), count);
	else if (input[i] == '%')
		count += write(1, "%%", 1);
	else
		count = -1;
	return (count);
}

int	check_string(char *input, va_list ap, int count)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '%')
		{
			count = check_conversion(input, i + 1, ap, count);
			if (count == -1)
				return (-1);
			i++;
			while (skip_flag(input, i) && input[i] != '\0')
				i++;
		}
		else
			count += write(1, &input[i], 1);
		i++;
	}
	return (count);
}

int	ft_printf(const char *input, ...)
{
	int		count;
	va_list	ap;

	if (!input || !*input)
		return (0);
	va_start(ap, input);
	count = 0;
	count = check_string((char *)input, ap, count);
	if (count == -1)
		return (-1);
	va_end(ap);
	return (count);
}

// int	main(void)
// {
// 	char	str[] = "Hello";

// 	printf("%d\n", ft_printf("M: %d\t", 10));
// 	printf("%d\n", printf("R: %d\t", 10));
// 	printf("%d\n", ft_printf("M: %c\t", str[0]));
// 	printf("%d\n", printf("R: %c\t", str[0]));
// 	printf("%d\n", ft_printf("M: %s\t", str));
// 	printf("%d\n", printf("R: %s\t", str));
// 	printf("%d\n", ft_printf("M: %p\t", &str));
// 	printf("%d\n", printf("R: %p\t", &str));
// 	printf("%d\n", ft_printf("M: %u\t", 429496728));
// 	printf("%d\n", printf("R: %u\t", 429496728));
// 	printf("%d\n", ft_printf("M: %x\t", 6726));
// 	printf("%d\n", printf("R: %x\t", 6726));
// 	printf("%d\n", ft_printf("M: %X\t", 3726));
// 	printf("%d\n", printf("R: %X\t", 3726));
// 	// // This gives an error
// 	// printf("%d\n", ft_printf("M: %%%"));
// 	// printf("%d\n", printf("R: %%%"));
// 	return (0);
// }
