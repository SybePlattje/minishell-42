/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:20:18 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/18 08:59:41 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char(char const str, char const *set)
{
	while (*set)
	{
		if (*set == str)
			return (1);
		set++;
	}
	return (0);
}

static int	search_end(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (is_char(s1[i], set) && i >= 0)
		i--;
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		end;

	if (!s1 || !set)
		return (NULL);
	while (is_char(*s1, set))
		s1++;
	end = search_end(s1, set);
	ptr = (char *)malloc(sizeof(char) * (end + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, end + 1);
	ptr[end] = '\0';
	return (ptr);
}

// int	main(void)
// {
// 	char	str[] = "123";
// 	char	set[] = "";
// 	char	*ptr;

// 	ptr = ft_strtrim(str, set);
// 	printf("%s\n", ptr);
// 	if (ptr)
// 		free(ptr);
// 	return (0);
// }
