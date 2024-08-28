/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:37:35 by splattje          #+#    #+#             */
/*   Updated: 2024/06/28 21:38:17 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

/**
 * @brief if str at index is \ and the next one isn't \0 print the next
 * one. If str at index is \ and the next one is \0 break the loop. Else
 * print the string
*/
static void	char_echo(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			ft_putchar_fd(str[i + 1], fd);
			i++;
		}
		else if (str[i] == '\\' && !str[i + 1])
			break ;
		else
			ft_putchar_fd(str[i], fd);
		i++;
	}
}

/**
 * @param token: pointer to the parser struct (t_parse)
 * @param mini: pointer to the minishell struct (t_mini)
 * @param index: index of where to start
 * @return returens 0 after printing
 * @brief if token->argv[index] is '$?' we print the exit code, else we print
 * the string. If the next index of argv doesn't return NULL and the next one
 * isn't empty it adds a whitespace
*/
static int	output_echo(t_parse *token, t_mini *mini, int index)
{
	while (token->argv[++index] != NULL)
	{
		if (ft_strncmp(token->argv[index], "$?", 2) == 0)
		{
			ft_putnbr_fd(g_exit_code, mini->out);
			if (token->argv[index + 1] != NULL)
				ft_putchar_fd(' ', mini->out);
		}
		else
		{
			char_echo(token->argv[index], mini->out);
			if (token->argv[index + 1] != NULL && token->argv[index][0])
				ft_putchar_fd(' ', mini->out);
		}
	}
	if (mini->check.new_line == 0)
		ft_putchar_fd('\n', mini->out);
	return (0);
}

/**
 * @param mini: pointer to the minishell struct (t_mini)
 * @param token: pointer to the parser struct (t_parse) that hold the info
 *  needed to be printed
 * @return returns 0 after being done printing
 * @brief prints the texst thats stored in token->argv
*/
int	print_echo(t_mini *mini, t_parse *token)
{
	int		index;

	if (!token->argv[1])
	{
		if (mini->check.new_line)
			return (ft_putstr_fd("", mini->out), 0);
		return (ft_putchar_fd('\n', mini->out), 0);
	}
	index = 0;
	return (output_echo(token, mini, index));
}
