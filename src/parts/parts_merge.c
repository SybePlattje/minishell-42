/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parts_merge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:03:50 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/06/28 21:37:06 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param mini: pointer to all the data (t_mini).
 * @param nr: number of lexer.
 * @param parts: parts of the current lexer that will be merge.
 * @brief adds lexer to mini.
*/
static void	add_lex(t_mini *mini, int nr, t_lex *new)
{
	t_lex	*next;
	t_lex	*lex;

	lex = mini->lex;
	if (nr == 0)
	{
		new->next = mini->lex;
		mini->lex = new;
	}
	else
	{
		while (lex->next->nr != nr && lex)
			lex = lex->next;
		next = lex->next;
		lex->next = new;
		new->next = next;
	}
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @param nr: number of lexer.
 * @param parts: parts of the current lexer that will be merge.
 * @brief puts a new lexer between with the first command.
 * @return 0 by succes. 1 by malloc fail.
*/
static int	add_to_lexer(t_mini *mini, int nr, t_parts *parts)
{
	t_lex	*new;

	new = new_lexer();
	new->str = ft_strdup(parts->str);
	if (!new->str)
		return (ft_error(NULL, "new->str", NULL, 0), 1);
	new->sort = CMD;
	add_lex(mini, nr, new);
	parts = parts->next;
	if (ft_strcmp(parts->next->str, " ") == 0)
		parts->next->keep = -1;
	return (0);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @param nr: number of lexer.
 * @param parts: parts of the current lexer that will be merge.
 * @param sort: sort set to 1. 
 * @brief checks the stringlen that is needed before merging.
 * @return len of string before merge. -1 by malloc fail.
*/
static int	get_len(t_mini *mini, int nr, t_parts *parts, int sort)
{
	t_parts	*current;
	int		len;

	if (sort != 0 && first_part_is_cmd(parts))
	{
		parts->keep = -1;
		parts = parts->next;
		if (add_to_lexer(mini, nr, parts))
			return (-1);
		parts->keep = -1;
	}
	len = 0;
	current = parts;
	while (current != NULL)
	{
		if (current->keep >= 0 && current->str
			&& !(current->next == NULL && ft_strcmp(current->str, " ") == 0))
			len += ft_strlen(current->str);
		current = current->next;
	}
	return (len);
}

/**
 * @param len: len of the part that will store in the new string.
 * @param parts: parts of the current lexer that will be merge.
 * @brief goes through lexer and checks if parts, merge.
 * @return NULL by failure, a string with the new lexer.
*/
static char	*merge(int len, t_parts *parts)
{
	t_parts	*current;
	char	*new;
	int		i;

	new = (char *)malloc (sizeof(char) * (len + 1));
	if (!new)
		return (ft_error(NULL, "new merge", NULL, 0), NULL);
	current = parts;
	len = 0;
	while (current != NULL)
	{
		i = 0;
		while (current->str && current->keep >= 0 && current->str[i]
			&& !(current->next == NULL && ft_strcmp(current->str, " ") == 0))
		{
			new[len] = current->str[i];
			i++;
			len++;
		}
		current = current->next;
	}
	new[len] = '\0';
	return (new);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @param sort: sort set to 1. 
 * @brief goes through lexer and checks if parts, merge.
 * @return 0 by succes, 1 by malloc failure.
*/
int	merge_parts(t_mini *mini, int sort)
{
	t_lex	*lexer;
	int		len;

	lexer = mini->lex;
	while (lexer != NULL)
	{
		if (lexer->parts != NULL)
		{
			free(lexer->str);
			len = get_len(mini, lexer->nr, lexer->parts, sort);
			if (len == -1)
				return (1);
			lexer->str = merge(len, lexer->parts);
			if (!lexer->str)
				return (1);
		}
		if (lexer->sort == 6)
			lexer->sort = 0;
		sort = lexer->sort;
		lexer = lexer->next;
	}
	return (0);
}
