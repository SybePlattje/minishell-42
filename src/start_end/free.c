/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:37:38 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/12 14:04:11 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param mini: pointer to access the parse in mini (t_mini)
 * @brief frees all parse
*/
void	free_parse(t_mini *mini)
{
	t_parse	*current;
	t_parse	*next;

	if (!mini->token)
		return ;
	current = mini->token;
	while (current != NULL)
	{
		if (current->cmd_path)
			free(current->cmd_path);
		if (current->argv)
			free_split(current->argv);
		next = current->next;
		free(current);
		current = next;
	}
	mini->token = NULL;
}

/**
 * @param mini: pointer to access the pipes in mini (t_mini)
 * @brief frees all pipes
*/
void	free_pipes(t_mini *mini)
{
	t_pipe	*current;
	t_pipe	*next;

	if (!mini->pipe)
		return ;
	current = mini->pipe;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	mini->pipe = NULL;
}

/**
 * @param var: pointer to variables (t_var)
 * @brief frees all var
*/
void	free_var(t_var *var)
{
	t_var	*current;
	t_var	*next;

	if (!var)
		return ;
	current = var;
	while (current != NULL)
	{
		if (current->value)
			free(current->value);
		next = current->next;
		free(current);
		current = next;
	}
}
