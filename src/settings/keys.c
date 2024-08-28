/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:26:52 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/13 11:49:20 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param signal: nr of signal.
 * @brief handles the signal in the program.
*/
void	handle_signals(int signals)
{
	if (signals == SIGINT)
	{
		write(1, "\n", STDOUT_FILENO);
		add(128 + signals);
		rl_on_new_line();
		rl_replace_line("", history_length - 1);
		rl_redisplay();
	}
}

/**
 * @param signal: nr of signal.
 * @brief handles the signal after forking by here_doc in the child.
*/
void	handle_heredoc(int signal)
{
	int	fd;

	if (signal == SIGINT)
	{
		add(128 + signal);
		fd = open("include/here_doc.txt", O_WRONLY | O_TRUNC, 0664);
		write(fd, "", 0);
		close(fd);
		exit (SIGINT);
	}
	else if (signal == SIGQUIT)
	{
		add(0);
		fd = open("include/here_doc.txt", O_WRONLY | O_TRUNC, 0664);
		write(fd, "", 0);
		close(fd);
		exit (SIGQUIT);
	}
}

/**
 * @param signal: nr of signal.
 * @brief handles the signal after forking by here_doc in the parent.
*/
void	handle_heredoc_parent(int signal)
{
	int	fd;

	if (signal == SIGINT || signal == SIGQUIT)
	{
		if (signal == SIGINT)
			add(128 + signal);
		else
			add(0);
		fd = open("include/here_doc.txt", O_WRONLY | O_TRUNC, 0664);
		write(fd, "", 0);
		close(fd);
		write(1, "\n", STDOUT_FILENO);
	}
}

/**
 * @param signal: nr of signal.
 * @brief handles the signal after forking in the child.
*/
void	handle_signals_child(int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
	{
		if (signal == SIGINT)
			add(128 + signal);
		else
			add(0);
		rl_replace_line("", history_length - 1);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
	}
}

/**
 * @param signal: nr of signal.
 * @brief handles the signal after forking in the parent.
*/
void	handle_signal_parent(int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
	{
		if (signal == SIGINT)
			add(128 + signal);
		else
			add(0);
		if (signal == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		else
			write(1, "\n", STDOUT_FILENO);
	}
}
