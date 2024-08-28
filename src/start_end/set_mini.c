/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:16:56 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/19 14:07:55 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param mini: pointer that contains all information of the program (t_mini)
 * @param argc: integer of amount of arguments.
 * @param argv: double pointer to arguments.
 * @brief prepares all data before going in to the program.
 * @return retuns 0 if overflow happened, 1 if not.
*/
int	memset_all(t_mini *mini, int argc, char **argv)
{
	ft_memset(mini, 0, sizeof(t_mini));
	mini->lex = new_lexer();
	if (!mini->lex)
		return (1);
	mini->token = new_parse(0);
	if (!mini->token)
		return (free_lexer(mini), 1);
	mini->in = STDIN_FILENO;
	mini->out = STDOUT_FILENO;
	mini->save_in = dup(STDIN_FILENO);
	mini->save_out = dup(STDOUT_FILENO);
	if (argc > 1)
		argv[1] = NULL;
	return (0);
}

/**
 * @param mini: pointer that contains all information of the program (t_mini).
 * @param exit_value: if 0 clean all, otherwise, reset only basic.
 * @brief cleans the program between different commands.
 * @return returns 0 with success. On error returns 1.
*/
int	clean(t_mini *mini, int exit_value)
{
	if (mini->check.here_doc)
	{
		close(mini->check.here_doc);
		if (unlink("include/here_doc.txt") == -1)
			ft_error(0, "here_doc", 0, 0);
	}
	free_parse(mini);
	free_lexer(mini);
	free_pipes(mini);
	dup2(mini->save_in, STDIN_FILENO);
	dup2(mini->save_out, STDOUT_FILENO);
	mini->in = STDIN_FILENO;
	mini->out = STDOUT_FILENO;
	if (exit_value == 0)
	{
		mini->lex = new_lexer();
		mini->token = new_parse(0);
		if (!mini->lex || !mini->token)
			return (1);
		ft_memset(&mini->check, 0, sizeof(mini->check));
	}
	mini->pipe = NULL;
	return (0);
}
