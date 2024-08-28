/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 09:02:56 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/19 08:20:40 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param lex: pointer to current lexer (t_lex).
 * @brief goes though the lexer from start pointer lex and
 * counts how many lexer of type CMD and QUOTE will follow.
 * @return returns a number of pairs.
*/
static int	find_pairs(t_lex *lex)
{
	t_lex	*current;
	int		pairs;

	current = lex;
	pairs = 0;
	if (current->sort != CMD)
		return (1);
	while (current->sort == CMD || current->sort == QUOTE)
	{
		pairs++;
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	return (pairs);
}

/**
 * @param lex: pointer to current lexer (t_lex).
 * @param pairs: amount of commands / lexers.
 * @brief start from current lexer and saves the amount of pairs
 * (lexers) in one argv to collect command and flags.
 * @return returns double string and NULL by failure.
*/
static char	**argv_parse(t_lex *lex, int pairs, int i)
{
	t_lex	*current;
	char	**argv;

	argv = (char **)malloc(sizeof(char *) * (pairs + 1));
	if (!argv)
		return (ft_error(NULL, "argv", NULL, 0), NULL);
	current = lex;
	while (i < pairs)
	{
		if (i != 0)
			current = current->next;
		argv[i] = ft_strdup(current->str);
		if (!argv[i])
		{
			free_split(argv);
			return (ft_error(NULL, "argv[i]", NULL, 0), NULL);
		}
		current->sort = -1;
		i++;
	}
	return (argv);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @param lex: pointer to current lexer (t_lex).
 * @param nr: number of current lexer.
 * @brief makes a new parse (incl pairs -> argv).
 * @return returns 0 by success,  and 1 by malloc failure.
*/
static int	filling_new_parse(t_mini *mini, t_lex *lex, int nr)
{
	t_parse	*current;
	int		pairs;
	int		i;

	current = mini->token;
	while (current->next != NULL)
		current = current->next;
	current->next = new_parse(nr);
	if (!current->next)
		return (1);
	current = current->next;
	current->sort = lex->sort;
	if (current->sort == CMD)
		pairs = find_pairs(lex);
	else
		pairs = 1;
	i = 0;
	current->argv = argv_parse(lex, pairs, i);
	if (!current->argv)
		return (1);
	current->argv[pairs] = NULL;
	return (0);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @brief gives all the pipes a number in order.
*/
static void	set_parser(t_mini *mini)
{
	t_parse	*current;
	int		pipe_nr;

	if (!mini->token)
		return ;
	current = mini->token;
	pipe_nr = 0;
	while (current != NULL)
	{
		if (current->sort == PIPE)
		{
			current->pipe_nr = pipe_nr;
			pipe_nr++;
		}
		current = current->next;
	}
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @brief from lexer to parse.
 * @return returns 0 by success,  and 1 by malloc failure.
*/
int	parser(t_mini *mini)
{
	t_lex	*lex;
	int		nr;

	nr = 0;
	lex = mini->lex;
	while (lex != NULL)
	{
		nr++;
		if (lex->sort != -1)
		{
			if (filling_new_parse(mini, lex, nr))
				return (1);
		}
		if (lex->next != NULL)
			lex = lex->next;
		else
			break ;
	}
	set_parser(mini);
	return (0);
}
