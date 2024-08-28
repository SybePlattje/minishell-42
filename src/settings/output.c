/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 09:54:57 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/19 08:14:20 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param mini: pointer to all the data (t_mini).
 * @param lexer: pointer to the lexer that the outfile contains (l_lex).
 * @brief checks the access of an outfile.
 * @return returns 0 by success, -1 when there is no access and 1 by open error. 
*/
static int	check_outfile(t_mini *mini, t_lex *lexer, int sort)
{
	char	*str;

	str = lexer->str;
	if (access(str, F_OK) != -1)
	{
		if (access(str, W_OK) == -1)
			return (ft_error(NULL, "outfile", NULL, 0), -1);
	}
	if (sort == OUTFILE)
		mini->check.outfile = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		mini->check.outfile = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (mini->check.outfile == -1)
		return (ft_error(NULL, "outfile", NULL, 0), 1);
	return (0);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @brief search throught the commands after outfiles.
 * @return returns 0 by success and 1 by open error. 
*/
int	get_output(t_mini *mini)
{
	t_lex	*current;
	int		sort;

	current = mini->lex;
	while (current != NULL)
	{
		if (current->sort == OUTFILE || current->sort == OUT_APP)
		{
			sort = current->sort;
			current->sort = OUTFILE;
			if (check_outfile(mini, current, sort) == -1)
				return (-1);
			else
				mini->out = mini->check.outfile;
		}
		current = current->next;
	}
	return (0);
}
