/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:01:03 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/13 12:48:03 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param str1: strings that contains a msg before error.
 * @param error: string that contains error msg.
 * @param str2: strings that contains a msg after error.
 * @param fault: if 0, checks errno, else checks own errno nr.
 * @brief print error msg and adds errno to the g_exit_value.
*/
void	ft_error(char *str1, char *error, char *str2, int fault)
{
	if (fault == 0)
	{
		add(errno);
		if (str1)
			ft_putstr_fd(str1, STDERR_FILENO);
		perror(error);
		if (str2)
			ft_putstr_fd(str2, STDERR_FILENO);
	}
	else
	{
		add(fault);
		if (str1)
			ft_putstr_fd(str1, STDERR_FILENO);
		if (error)
			ft_putstr_fd(error, STDERR_FILENO);
		if (str2)
			ft_putstr_fd(str2, STDERR_FILENO);
	}
}

/**
 * @param limiter: string with the limiter from here_doc.
 * @param i: integer that contains the line number.
 * @brief gives an error msg when the SIGQUIT is pressed 
 * during the here_doc input.
*/
void	print_error_heredoc(char *limiter, int i)
{
	int	fd;

	ft_putstr_fd("\nwarning: here-document at line ", 2);
	ft_putnbr_fd(i, 2);
	ft_putstr_fd(" delimited by end-of-file ", 2);
	ft_error("(wanted `", limiter, "')\n", 1);
	fd = open("include/here_doc.txt", O_WRONLY | O_TRUNC, 0664);
	write(fd, "", 0);
	close(fd);
}

void	*line_error(int *exit_value)
{
	exit_value[0] = 1;
	ft_error(NULL, "str", NULL, 0);
	return (NULL);
}
