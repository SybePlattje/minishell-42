/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:18:46 by splattje          #+#    #+#             */
/*   Updated: 2024/03/19 08:12:08 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param head: pointer to the first of the variables (t_var).
 * @param new: pointer to the newest variable (t_var).
 * @brief adds the new variable at the end.
 * @return returns head.
*/
t_var	*var_add_back(t_var *head, t_var *new)
{
	t_var	*current;

	if (head == NULL)
		return (NULL);
	current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	return (head);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @brief creates a new struct by EXPORT variables(t_var).
 * @return returns 0 by success,  and 1 by malloc failure.
*/
int	add_var(t_mini *mini)
{
	t_lex	*current;
	t_var	*new;

	current = mini->lex;
	while (current != NULL)
	{
		if (current->sort == VAR_DEF)
		{
			new = new_var(current->str);
			if (!new)
				return (1);
			mini->var = var_add_back(mini->var, new);
			current->sort = -1;
		}
		current = current->next;
	}
	return (0);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @brief creates a new struct by GLOBAL variable(t_var).
 * @return returns 0 by success,  and 1 by malloc failure.
*/
t_var	*new_var(char *data)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	if (var == NULL)
		return (NULL);
	var->value = ft_strdup(data);
	if (var->value == NULL)
	{
		free(var);
		return (ft_error(NULL, "var", NULL, 0), NULL);
	}
	var->next = NULL;
	return (var);
}

/**
 * @brief strjoin and free of input strings.
 * @return returns 0 by success,  and 1 by malloc failure.
*/
char	*join_and_free(char *str1, char *str2)
{
	char	*new;

	new = ft_strjoin(str1, str2);
	if (!new)
		ft_error(NULL, "new", NULL, 0);
	free(str1);
	free(str2);
	return (new);
}
