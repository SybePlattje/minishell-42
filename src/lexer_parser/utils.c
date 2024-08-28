/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 08:04:11 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/19 08:20:03 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param nr: integer with number of parser.
 * @brief makes a new parser and saves the number in it.
 * @return pointer to a new parser (t_parse).
*/
t_parse	*new_parse(int nr)
{
	t_parse	*new;

	new = (t_parse *)malloc(sizeof(t_parse));
	if (!new)
		return (ft_error(NULL, "new parse", NULL, 0), NULL);
	new->argv = NULL;
	new->cmd_path = NULL;
	new->file = -1;
	new->sort = -1;
	new->pipe_nr = -1;
	new->nr = nr;
	new->next = NULL;
	return (new);
}

/**
 * @brief makes a new lexer..
 * @return pointer to a new lexer (t_lex).
*/
t_lex	*new_lexer(void)
{
	t_lex	*new;

	new = (t_lex *)malloc(sizeof(t_lex));
	if (!new)
		return (ft_error(NULL, "new lex", NULL, 0), NULL);
	new->str = NULL;
	new->sort = -1;
	new->parts = NULL;
	new->next = NULL;
	return (new);
}

/**
 * @param line: string with input.
 * @param i: index with start position.
 * @param j: len 
 * @brief cleans the line from i with the len of j.
*/
void	clean_line(char *line, int i, int j)
{
	while (i < j)
	{
		line[i] = ' ';
		i++;
	}
}

/**
 * @param mini: pointer that contains all data (t_mini).
 * @brief goes through the lexer and checks for each the
 * sort. Saves the amount in mini->check.
 * @return pointer to a new lexer (t_lex).
*/
void	count_sorts(t_mini *mini)
{
	t_lex	*current;

	current = mini->lex;
	while (current != NULL)
	{
		if (current->sort == INFILE)
			mini->check.infile++;
		else if (current->sort == OUTFILE || current->sort == OUT_APP)
			mini->check.outfile++;
		else if (current->sort == HERE_DOC)
			mini->check.here_doc++;
		else if (current->sort == PIPE)
			mini->check.pipes++;
		else if (current->sort == VAR_DEF)
			mini->check.var_def++;
		current = current->next;
	}
}
