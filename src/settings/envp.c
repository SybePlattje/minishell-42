/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:27:53 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/19 14:09:13 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param mini: pointer to all the data (t_mini).
 * @param path: string with all the path names.
 * @brief split string with path in a double array.
 * @return by succes 0, else 1 malloc error.
*/
static int	make_paths(t_mini *mini, char *path)
{
	mini->envp_path = ft_split(path, ':');
	if (!mini->envp_path)
		return (ft_error(NULL, "mini->envp_path", NULL, 0), 1);
	return (0);
}

/**
 * @param mini: pointer to all the data (t_mini)
 * @param i: integer with line number.
 * @brief gives an error msg when the SIGQUIT is pressed.
 * during the here_doc input.
 * @return by succes 0, when not found 1.
*/
int	get_paths(t_mini *mini, t_var *var)
{
	t_var	*current;

	current = var;
	while (current != NULL)
	{
		if (ft_strncmp(current->value, "PATH", 4) == 0)
		{
			if (make_paths(mini, current->value + 5))
				return (1);
			else
				return (0);
		}
		current = current->next;
	}
	mini->envp_path = NULL;
	return (0);
}
