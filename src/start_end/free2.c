/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:05:25 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/12 14:04:57 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param split: double pointer 
 * @brief frees a double pointer
*/
void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split || !*split)
		return ;
	while (1)
	{
		free(split[i]);
		i++;
		if (!split[i])
			break ;
	}
	free(split);
}

/**
 * @param lex: pointer to access the parts in lex (t_lex)
 * @brief frees all parts
*/
void	free_parts(t_lex *lex)
{
	t_parts	*current;
	t_parts	*next;

	if (!lex->parts)
		return ;
	current = lex->parts;
	while (current != NULL)
	{
		if (current->str)
			free(current->str);
		next = current->next;
		free(current);
		current = next;
	}
	lex->parts = NULL;
}

/**
 * @param mini: pointer to access the lex in mini (t_mini)
 * @brief frees all lexer
*/
void	free_lexer(t_mini *mini)
{
	t_lex	*current;
	t_lex	*next;

	if (!mini->lex)
		return ;
	current = mini->lex;
	while (current != NULL)
	{
		if (current->str)
			free(current->str);
		free_parts(current);
		next = current->next;
		free(current);
		current = next;
	}
	mini->lex = NULL;
}
