/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 07:27:07 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/19 08:21:18 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param l: string with the input.
 * @param current: pointer to current lexer (t_lex).
 * @brief makes a substring for every split.
 * @return 0 by success, 1 by failure. 
*/
static int	make_substr(char *l, t_lex *current)
{
	int	i;

	i = 0;
	if (*l == '<' || *l == '>')
		current->str = make_sort_1(l, i, current);
	else if (*l == '|')
	{
		current->sort = PIPE;
		current->str = ft_strdup("|");
	}
	else if (*l == '\'' || *l == '"')
		current->str = make_sort_3(l, i + 1, current);
	else
		current->str = make_sort_4(l, i, current);
	if (!current->str)
		return (ft_error(NULL, "current->str\n", NULL, 0), 1);
	return (0);
}

/**
 * @param mini: pointer that contains all data (t_mini).
 * @param l: string with the input.
 * @brief splits the string in pieces and saves it in t_lex.
 * @return 0 by success, 1 by failure. 
*/
static int	lexer_sort(t_mini *mini, char *l)
{
	t_lex	*current;
	int		i;

	current = mini->lex;
	i = 0;
	while (l[i])
	{
		if (i == 0 || l[i] == '<' || l[i] == '>' || l[i] == '\'' || l[i] == '|'
			|| l[i] == '"' || (l[i] != ' ' && l[i] != '\n'))
		{
			if (make_substr(l + i, current))
				return (1);
			i += ft_strlen(current->str);
		}
		else
			i++;
		if (current->str)
		{
			current->next = new_lexer();
			if (current->next == NULL)
				return (1);
			current = current->next;
		}
	}
	return (0);
}

/**
 * @param mini: pointer that contains all data (t_mini).
 * @brief gives the lexers a number in order
*/
static void	numb_lexer(t_mini *mini)
{
	t_lex	*current;
	int		i;

	i = 0;
	current = mini->lex;
	while (current != NULL)
	{
		current->nr = i;
		i++;
		current = current->next;
	}
}

/**
 * @param mini: pointer that contains all data (t_mini).
 * @param l: string with the input.
 * @brief handles all parts of the lexer.
 * @return 0 by succes, 1 by failure.
*/
int	lexer(t_mini *mini, char *l)
{
	if (ft_strchr(l, 'n') != 0 && ft_strchr(l, '-') != 0)
		check_newline_echo(mini, l);
	if (lexer_sort(mini, l))
		return (1);
	if (mini->lex->str == NULL)
		return (-1);
	count_sorts(mini);
	numb_lexer(mini);
	return (0);
}
