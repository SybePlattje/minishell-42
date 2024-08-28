/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parts_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:06:07 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/20 08:17:52 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param parts: pointer to head of parts (t_parts).
 * @param str: string that will be saved in the new part.
 * @brief creates a new t_parts *, saves the string in there
 * and add it to the end of the linked list.
 * @return pointer to the head of parts, by failure NULL.
*/
t_parts	*part_addback(t_parts *parts, char *str)
{
	t_parts	*new;
	t_parts	*last;

	if (!str)
		return (ft_error(NULL, "str part", NULL, 0), NULL);
	new = (t_parts *)malloc(sizeof(t_parts));
	if (!new)
		return (ft_error(NULL, "new", NULL, 0), NULL);
	new->str = str;
	new->keep = -1;
	new->next = NULL;
	if (parts == NULL)
		return (new);
	last = parts;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	return (parts);
}

/**
 * @param parts: pointer to head of the parts (t_parts).
 * @param str: string with the input.
 * @param i: current char.
 * @brief makes a struct for every special sign and adds it
 * to the end of parts.
 * @return returns the head of parts.
*/
t_parts	*add_parts(t_parts *parts, char *str, int i)
{
	if (str[i] == '"')
		return (part_addback(parts, ft_strdup("\"")));
	else if (str[i] == '\'')
		return (part_addback(parts, ft_strdup("'")));
	else if (str[i] == ' ')
		return (part_addback(parts, ft_strdup(" ")));
	else if (str[i] == '\\')
		return (part_addback(parts, ft_strdup("\\")));
	else if (str[i] == '/')
		return (part_addback(parts, ft_strdup("/")));
	return (NULL);
}

int	space_handling(int *space)
{
	if (*space == 0)
	{
		*space = 1;
		return (1);
	}
	return (-2);
}

/**
 * @param parts: pointer to head of the parts (t_parts).
 * @brief checks if the input starts with a pipe.
 * @return 1 when it is the case, zero when not.
*/
int	first_part_is_cmd(t_parts *parts)
{
	t_parts	*first;
	t_parts	*current;

	first = parts;
	if (first->next == NULL || first->keep != -2)
		return (0);
	current = first->next;
	if (current->keep != 1 || current->next == NULL)
		return (0);
	first = current->next;
	if (first->keep == -2 && first->next != NULL)
	{
		if (ft_strcmp(first->next->str, " ") == 0
			|| ft_strcmp(first->next->str, "|") == 0)
			return (1);
	}
	return (0);
}

/**
 * @param str: string that include the dollar sign.
 * @brief checks if the string contains brackets,
 * @return if brackets returns 1 else 0.
*/
int	check_brackets(char *str)
{
	if (str[0] == '{')
		return (1);
	return (0);
}
