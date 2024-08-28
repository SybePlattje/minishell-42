/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parts_proces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:57:40 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/20 08:28:41 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param parts: current part.
 * @param c: char after the slash.
 * @param fault: pointer integer that turns 1 by a malloc fault.
 * @brief adds slashes to keep them on the end.
 * @return returns parts.
*/
static t_parts	*check_slash(t_parts *current, char c, int *malloc_fault)
{
	if (c == '\'' && ft_strcmp(current->str, "\\") == 0)
	{
		free(current->str);
		current->keep = 0;
		current->str = ft_strdup("\\\\");
		if (!current->str)
		{
			malloc_fault[0] = 1;
			return (ft_error(NULL, "current->str", NULL, 0), current);
		}
	}
	if (c == '\"' && ft_strcmp(current->str, "\\") == 0)
	{
		current->keep = 0;
		if (current->next)
			current = current->next;
		current->keep = 1;
		if (ft_strcmp(current->str, "\"") == 0)
			current->keep = 0;
	}
	return (current);
}

/**
 * @param parts: current part.
 * @param c: sigle or double quote
 * @param fault: integer that turns 1 by a malloc fault.
 * @brief returns keep value for next parts depending of the current quote.
 * @return 0 by success and 1 by malloc fault.
*/
static int	change_keep_parts(t_parts *part, char c, int malloc_fault)
{
	t_parts	*current;

	current = part;
	while (current != NULL && current->str[0] != c)
	{
		if (c == '\'')
		{
			current->keep = 0;
			current = check_slash(current, c, &malloc_fault);
		}
		else
		{
			current->keep = 1;
			current = check_slash(current, c, &malloc_fault);
		}
		if (current->next != NULL)
			current = current->next;
		else
			break ;
	}
	if (ft_strcmp(current->str, "\'") == 0
		|| ft_strcmp(current->str, "\"") == 0)
		current->keep = -2;
	return (malloc_fault);
}

/**
 * @param parts: current part.
 * @brief set the keep and redirect for change keep in parts.
 * @return 0 by succes and 1 by malloc fault.
*/
static int	change_keep(t_parts *part)
{
	t_parts	*current;
	char	c;

	if (ft_strcmp(part->str, "'") == 0)
		c = '\'';
	else
		c = '"';
	current = part;
	current->keep = -2;
	if (current->next != NULL)
		current = current->next;
	else
		return (0);
	return (change_keep_parts(current, c, 0));
}

/**
 * @param parts: current part.
 * @param fault: pointer integer that turns 1 by a malloc fault.
 * @brief checks part on quote, slash or other char.
 * @return returns parts.
*/
static t_parts	*split_cases_part(t_parts *parts, int *fault)
{
	if (ft_strcmp(parts->str, "'") == 0 || ft_strcmp(parts->str, "\"") == 0)
	{
		if (change_keep(parts))
		{
			fault[0] = 1;
			return (parts);
		}
	}
	else if (parts->str[0] == '\\')
	{
		parts->keep = 1;
		if (parts->next)
			parts = parts->next;
		parts->keep = 1;
	}
	else if (parts->str[0] != ' ')
		parts->keep = 1;
	return (parts);
}

/**
 * @param lexer: lexer that contains parts.
 * @brief goes though the parts and checks what to keep.
 * @return returns 0 by success, and 1 by error.
*/
int	proces_parts(t_lex *lexer)
{
	t_parts	*parts;
	int		space;
	int		fault;

	parts = lexer->parts;
	space = 0;
	fault = 0;
	while (parts != NULL)
	{
		if (parts->str && (ft_strcmp(parts->str, "'") == 0
				|| ft_strcmp(parts->str, "\"") == 0 || parts->str[0] == '\\'
				|| parts->str[0] != ' '))
		{
			parts = split_cases_part(parts, &fault);
			if (fault == 1)
				return (1);
		}
		if (parts->str && ft_strcmp(parts->str, " ") == 0)
			parts->keep = space_handling(&space);
		else
			space = 0;
		while (parts != NULL && parts->keep != -1)
			parts = parts->next;
	}
	return (0);
}
