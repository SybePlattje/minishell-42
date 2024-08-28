/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:27:45 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/19 08:46:19 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param mini: pointer to the minishell struct (t_mini)
 * @return returns 1 if PWD=/ wasn't found, 0 if it is found
 * @brief prints the path of where you are within the system
*/
int	print_pwd(t_mini *mini)
{
	t_var	*var;

	var = mini->var;
	while (var != NULL)
	{
		if (ft_strncmp(var->value, "PWD=/", 5) == 0)
		{
			ft_putendl_fd(var->value + 4, mini->out);
			return (0);
		}
		var = var->next;
	}
	return (1);
}

/**
 * @param mini: pointer to the minishell struct (t_mini)
 * @param envp: pointer to the stuct that holds the envirenment variables (t_var)
 * @return returns 0 when it's done printing every environment variable
 * @brief prints the environment variables.
*/
int	print_environment(t_mini *mini, t_var *envp)
{
	t_var	*current;

	current = envp;
	while (current != NULL)
	{
		if (ft_strchr(current->value, '=') != 0)
			ft_putendl_fd(current->value, mini->out);
		current = current->next;
	}
	return (0);
}
