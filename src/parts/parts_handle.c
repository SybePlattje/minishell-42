/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parts_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:06:12 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/06/28 21:36:23 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param option: if 1 checks for splitting 1 char,
 * if 2 checks where to end a string for splitting.
 * @brief compares char with special signs.
 * @return returns 1 with match, otherwise 0.
*/
static int	check_char_parts(char c, int option)
{
	if (option == 1)
	{
		if (c == '"' || c == '\'' || c == ' ' || c == '\\' || c == '/')
			return (1);
		return (0);
	}
	if (!(c > 32 && c < 35) && !(c > 41 && c < 48) && !(c > 57 && c < 65)
		&& !(c > 90 && c < 95) && !(c > 122 && c < 127))
		return (1);
	return (0);
}

/**
 * @param str: string that contains quotes or dollar sign.
 * @brief divide the string in parts (t_parts).
 * @return returns struct of parts or NULL by failure.
*/
static t_parts	*split_parts(char *str)
{
	t_parts	*parts;
	int		i;
	int		j;

	i = 0;
	parts = NULL;
	while (str[i])
	{
		if (check_char_parts(str[i], 1))
			parts = add_parts(parts, str, i);
		else
		{
			j = i;
			i++;
			while (str[i] && check_char_parts(str[i], 2))
				i++;
			parts = part_addback(parts, ft_substr(str, j, i - j));
			i--;
		}
		if (!parts)
			break ;
		i++;
	}
	return (parts);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @brief checks if a lexer contains quotes or dollar signs.
 * @return returns 0 by success,  and 1 by error.
*/
int	handle_parts(t_mini *mini)
{
	t_lex	*lex;
	
	lex = mini->lex;
	while (lex != NULL)
	{
		if (lex->str && (ft_strchr(lex->str, '\'') != 0
				|| ft_strchr(lex->str, '"') != 0
				|| ft_strchr(lex->str, '$') != 0))
		{
			lex->parts = split_parts(lex->str);
			if (!lex->parts)
				return (1);
			proces_parts(lex);
		}
		lex = lex->next;
	}
	return (0);
}
