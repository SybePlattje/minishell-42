/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:54:19 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/13 11:56:18 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param str: the current line the user inputted
 * @return retuns 0 if there are only spaces or tabs, 1 if else.
 * @brief checks if the string contains only spaces or tabs.
*/
int	empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static int	is_last_pipe(char *str)
{
	int	i;

	if (ft_strchr(str, '|') == 0)
		return (0);
	i = ft_strlen(str) - 1;
	while (i && str[i] && str[i] == ' ')
		i--;
	if (i <= 0)
		return (0);
	if (str[i] == '|')
		return (1);
	return (0);
}

/**
 * @param str: string that contains the input line.
 * @param exit_value: int that becomes 1 by malloc fail.
 * @brief adds new commands when input ends with a pipe.
 * @return returns char* of a complet string.
*/
char	*check_last_pipe(char *str, int *exit_value)
{
	char	*line;
	char	*new_str;

	if (!str)
		return (line_error(exit_value));
	while (is_last_pipe(str))
	{
		line = readline("> ");
		if (!line)
		{
			exit_value[0] = 1;
			return (NULL);
		}
		new_str = ft_strjoin(str, line);
		free(str);
		free(line);
		if (!new_str)
		{
			exit_value[0] = 1;
			return (ft_error(0, "join", 0, 0), NULL);
		}
		str = new_str;
	}
	return (str);
}

/**
 * @param str: string that contains the input line.
 * @brief checks (wrong use of) special chars.
 * @return returns 0 by success and -1 by wrong use. 
*/
int	first_checks(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if ((str[i] == '|' || str[i] == ';' || str[i] == '&')
		&& (str[i + 1] == '\0' || str[i + 1] == ' '))
	{
		ft_error("minishell: ", "syntax error near unexpected token `", 0, 1);
		ft_putchar_fd(str[i], 2);
		return (ft_putstr_fd("\'\n", 2), -1);
	}
	if ((str[0] == '<' && str[1] == '\0')
		|| (str[0] == '>' && str[i + 1] == '\0')
		|| (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '\0')
		|| (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '\0'))
	{
		ft_error("minishell: ", "syntax error near unexpected token", 0, 1);
		ft_putstr_fd("`newline\'\n", STDERR_FILENO);
		return (-1);
	}
	if (str[i] == '#')
		return (-1);
	return (0);
}
