/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:24:22 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/19 08:20:23 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param token: pointer to the current token (t_parse).
 * @brief saves the commandname in the token that is stored
 * in argv[0].
 * @return returns a string with the name,  and NULL by malloc failure.
*/
static char	*make_substr_parser(t_parse *token)
{
	char	*str;

	str = ft_strdup(token->argv[0]);
	if (!str)
		return (ft_error(NULL, "split_cmd", NULL, 0), NULL);
	free(token->argv[0]);
	free(token->argv);
	return (str);
}

/**
 * @param str: string with the input to check.
 * @param i: pointer to remembers the len of the next cmd.
 * @brief goes through the string and checks if there is one 
 * or more cmds. It also saves the lenght of the next argv. 
 * @return returns 1 by one command, else 2.
*/
static int	get_amount_str(char *str, int *i)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == ' ')
		{
			*i = j;
			while (str[j] && str[j] == ' ')
				j++;
			if (str[j] == '\0')
				return (1);
			else
				return (2);
		}
		j++;
	}
	*i = j;
	return (1);
}

/**
 * @param str: string with the commands.
 * @param argv: double pointer.
 * @param option: int that gives an option what to free.
 * @brief frees the argv when there is a malloc failure during
 * the proces.
 * @return returns NULL.
*/
static void	*free_split_cmd(char *str, char **argv, int option)
{
	free(str);
	if (option == 1)
	{
		ft_error(NULL, "argv[0]", NULL, 0);
		free(str);
		free(argv);
	}
	else if (option == 2)
	{
		ft_error(NULL, "argv[1]", NULL, 0);
		free(str);
		free(argv[0]);
		free(argv);
	}
	return (NULL);
}

/**
 * @param token: pointer to current token (t_parse).
 * @param i: index of start point for splitsing.
 * @brief prepares a double pointer for argv and  saves the
 * commands in it.
 * @return double pointer, NULL by failure.
*/
char	**split_cmd(t_parse *token, int i)
{
	char	*str;
	char	**argv;
	int		amount;

	str = make_substr_parser(token);
	if (!str)
		return (NULL);
	amount = get_amount_str(str, &i);
	argv = (char **)malloc(sizeof(char *) * (amount + 1));
	argv[amount] = NULL;
	argv[0] = ft_substr(str, 0, i);
	if (!argv[0])
		return (free_split_cmd(str, argv, 1));
	if (amount > 1)
	{
		argv[1] = ft_substr(str, i + 1, ft_strlen(str) - i);
		if (!argv[1])
			return (free_split_cmd(str, argv, 1));
	}
	return (free(str), argv);
}
