/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_substr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:08:41 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/19 08:22:06 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param l: string with the input.
 * @param i: current index number.
 * @param lexer: pointer where the substring is stored in (t_lex).
 * @brief special signs: gives the right sort number to a lexer.
 * @return the new substring, NULL by failure.
*/
char	*make_sort_1(char *l, int i, t_lex *lexer)
{
	char	*str;
	int		j;

	if (l[i] == '$')
		j = 0;
	else
		j = 1;
	if (l[i] == '<' && l[i + 1] == '<')
		lexer->sort = HERE_DOC;
	else if (l[i] == '<')
		lexer->sort = INFILE;
	else if (l[i] == '>' && l[i + 1] == '>')
		lexer->sort = OUT_APP;
	else if (l[i] == '>')
		lexer->sort = OUTFILE;
	while (l[i + j] == ' ' || l[i + j] == '>' || l[i + j] == '<')
		j++;
	while (l[i + j] && l[i + j] != ' ' && l[i + j] != '|')
		i++;
	str = ft_substr(l, j, i);
	clean_line(l, 0, i + j);
	return (str);
}

/**
 * @param l: string with the input.
 * @param i: current index number.
 * @param lexer: pointer where the substring is stored in (t_lex).
 * @brief qoutes: gives the right sort number to a lexer.
 * @return the new substring, NULL by failure.
*/
char	*make_sort_3(char *l, int i, t_lex *lexer)
{
	char	*new;
	int		open;

	lexer->sort = QUOTE;
	open = 1;
	while (l[i])
	{
		if ((l[i] == '\0') && open == 1)
		{
			ft_error(NULL, "no quote found: ", NULL, 1);
			return (ft_strdup(l));
		}
		else if (l[i] == *l && open == 1)
			open = 0;
		else if (l[i] == *l && open == 0)
			open = 1;
		i++;
		if ((l[i] == '<' || l[i] == '>' || l[i] == '|') && open == 0)
			break ;
	}
	new = ft_substr(l, 0, i);
	if (!new)
		return (NULL);
	return (new);
}

/**
 * @param l: string with the input.
 * @param i: current index number.
 * @param lexer: pointer where the substring is stored in (t_lex).
 * @brief commands: gives the right sort number to a lexer.
 * @return the new substring, NULL by failure.
*/
char	*make_sort_4(char *l, int i, t_lex *lexer)
{
	lexer->sort = CMD;
	if (l[i] == ' ')
		ft_substr(l, 0, 1);
	while (l[i] && l[i] != '|' && l[i] != ' ' && l[i] != '\n')
		i++;
	return (ft_substr(l, 0, i));
}
