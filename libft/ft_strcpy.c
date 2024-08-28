/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/29 15:13:31 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/29 15:20:25 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	index;

	if (src == NULL || dest == NULL)
		return (src);
	index = 0;
	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}
