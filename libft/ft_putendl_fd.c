/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:04:09 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/13 10:41:53 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @param s: string with the variable.
 * @param fd: file discriptor
 * @brief prints given string and adds a newline.
*/
void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}

// int	main(void)
// {
// 	char	str[] = "Print this string";
// 	int		fd;

// 	fd = 1;
// 	ft_putendl_fd(str, fd);
// 	return (0);
// }
