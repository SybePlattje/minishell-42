/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/29 15:02:57 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/29 15:10:57 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char *src, size_t n)
{
	int	index;

	if (dest == NULL || src == NULL)
		return (src);
	index = 0;
	while (src[index] != '\0' && n > 0)
	{
		dest[index] = src[index];
		index++;
		n--;
	}
	while (n > 0)
		dest[index++] = '\0';
	return (dest);
}
