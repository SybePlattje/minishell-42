/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:38:06 by splattje          #+#    #+#             */
/*   Updated: 2024/03/13 12:03:13 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param var_name: the name from token->arg[index]
 * @param current: pointer to the current variable struct (t_var)
 * @param next: pointer to the next variable struct (t_var)
 * @param prev: pointer to the previous variable struct (t_var)
 * @brief checks if name exists as is, not part, complete name. And removes it.
*/
static void	unset(char *var_name, t_var **current, t_var **next, t_var **prev)
{
	*next = (*current)->next;
	if (ft_strncmp(var_name, (*current)->value, ft_strlen(var_name)) == 0
		&& ((*current)->value[ft_strlen(var_name)] == '\0'
			|| (*current)->value[ft_strlen(var_name)] == '='))
	{
		free((*current)->value);
		free(*current);
		if ((*prev) != NULL)
		{
			(*prev)->next = *next;
			*current = *next;
		}
		else
			*current = *next;
	}
	else
	{
		*prev = *current;
		*current = *next;
	}
}

/**
* @param unset_tok: pointer to the parser struct (t_parse) 
* @param var: pointer to the variables stuct (t_var)
* @return returns 0 when done
* @brief unsets the variables that are in unset_tok->argv  
*/
int	unset_env_var(t_parse *unset_tok, t_var *var)
{
	t_var	*next;
	t_var	*prev;
	t_var	*current;
	t_var	*start;
	int		index;

	current = var;
	start = var;
	next = NULL;
	prev = NULL;
	if (unset_tok->nr != 1 || unset_tok->next != NULL)
		return (0);
	if (unset_tok->argv && unset_tok->argv[1] == NULL)
		return (0);
	index = 1;
	while (unset_tok->argv[index])
	{
		while (current != NULL)
			unset(unset_tok->argv[index], &current, &next, &prev);
		current = start;
		index++;
	}
	return (0);
}
