/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:31:10 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/02/20 14:04:36 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_chars(char *str, char c)
{
	int	len;

	len = 0;
	while (*str)
	{
		if (*str != c)
			len++;
		str++;
	}
	return (len);
}

char	*ft_remove_char(char *str, char c)
{
	char	*new;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	len = count_chars(str, c);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] != c)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}
