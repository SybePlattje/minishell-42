/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newl_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:31:19 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/13 13:17:44 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param line: string with input.
 * @param end: last index in string where the flag is found.
 * @brief clears the string with spaces after a correct flag.
*/
static void	make_space(char *line, int end)
{
	int	i;

	if (!line || end <= 0)
		return ;
	i = 0;
	while (i < end && line[i])
	{
		line[i] = ' ';
		i++;
	}
}

/**
 * @param line: string with input.
 * @brief checks the found newlineflags. Clears after reading.
 * @return 1 if the newline flag is correct and 0 if not.
*/
static int	check_nnn(char *line)
{
	int	i;

	i = 0;
	if (line[i] != '-')
		return (0);
	while (1)
	{
		if (line[i] != '-')
			return (1);
		else
			i++;
		while (line[i] && line[i] == 'n')
			i++;
		if (line[i] != '\0' && line[i] != ' ')
			return (0);
		make_space(line, i);
		i = 0;
		while (line[i] && line[i] == ' ')
			i++;
	}
	return (1);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @param line: string with input.
 * @brief checks the first newlineflags. Clears it when 
 * it are corrent newlineflags. Saves result in
 * mini->check.new_line.
*/
static void	check_first_flag(t_mini *mini, char *line)
{
	int	i;

	mini->check.new_line = 0;
	if (line && *line == '"')
	{
		i = 0;
		if (line[i + i])
			i++;
		mini->check.new_line = 1;
		while (line[i] && line[i] != ' ')
		{
			if (line[i] != '-' && line[i] != 'n')
				mini->check.new_line = 0;
			i++;
		}
		if (mini->check.new_line == 1)
			make_space(line, i + 1);
	}
	else if (ft_strncmp(line, "-n", 2) == 0)
		mini->check.new_line = check_nnn(line);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @param line: string with input.
 * @brief checks the newlineflags that follow the first part.
 * Clears it when it are corrent newlineflags. Saves result in
 * mini->check.new_line.
*/
static void	check_more_flags(t_mini *mini, char *line)
{
	int	new;
	int	i;

	i = 0;
	if (*line == '"')
	{
		if (line[i + 1])
			i++;
		while (line[i] && line[i] != '"')
		{
			new = 1;
			if (line[i] != '-' && line[i] != 'n')
				new = 0;
			i++;
		}
		if (new == 1)
			make_space(line, i + 1);
	}
	else if (ft_strncmp(line, "-n", 2) == 0)
		mini->check.new_line = check_nnn(line);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @param line: string with input.
 * @brief checks if echo needs a newline or not. 
 * Saved in mini->check.new_line
*/
void	check_newline_echo(t_mini *mini, char *line)
{
	while (line && *line)
	{
		if (ft_strncmp(line, "echo ", 5) == 0)
		{
			while (*line && *line != ' ')
				line++;
			if (*line == '\0')
				return ;
			line++;
			check_first_flag(mini, line);
			if (mini->check.new_line == 1)
			{
				while (*line && *line == ' ')
					line++;
				check_more_flags(mini, line);
			}
		}
		if (*line)
			line++;
	}
}
