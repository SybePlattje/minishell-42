/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:05:43 by mvan-ess          #+#    #+#             */
/*   Updated: 2023/10/05 12:05:45 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counting(char const *s, char c)
{
	int	count;
	int	i;
	int	first;

	count = 0;
	i = 0;
	first = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && first == 0)
		{
			first = 1;
			count++;
		}
		else if (s[i] == c)
			first = 0;
		i++;
	}
	return (count);
}

static void	ft_free(char **split, int j)
{
	while (j >= 0)
	{
		j--;
		free(split[j]);
	}
	free(split);
}

static char	**splitting(char **split, const char *s, char c)
{
	size_t	i;
	size_t	j;
	int		new;

	i = -1;
	j = 0;
	new = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && new < 0)
			new = i;
		else if ((s[i] == c || i == ft_strlen(s)) && new >= 0)
		{
			split[j] = ft_substr(s, new, i - new);
			if (!(split[j]))
			{
				ft_free(split, j);
				return (NULL);
			}
			j++;
			new = -1;
		}
	}
	split[j] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		words;

	if (!s)
		return (0);
	words = counting(s, c) + 1;
	split = malloc(sizeof(char *) * words);
	if (!split)
		return (NULL);
	split = splitting(split, s, c);
	if (!split)
		return (NULL);
	return (split);
}

// int	main(void)
// {
// 	char	str[] = " Testing this string ";
// 	char	c;
// 	char	**ptr;

// 	c = ' ';
// 	ptr = ft_split(str, c);
// 	printf("%s\n%s\n%s", ptr[0], ptr[1], ptr[2]);
// 	if (ptr)
// 		free(ptr);
// 	return (0);
// }
