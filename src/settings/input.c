/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:25:24 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/19 14:11:08 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param limiter: string with the limiter for the here_doc.
 * @param temp_fd: fd from the here_doc file.
 * @brief gets input for the here_doc with readline.
 * @return returns 1 by malloc failure and 0 by success.
*/
static int	get_next_line_input(char *limiter, int temp_fd)
{
	char	*str;
	char	*new_lim;
	int		i;

	new_lim = ft_strjoin(limiter, "\n");
	if (!new_lim)
		return (ft_error(NULL, "limiter", NULL, 0), 1);
	i = 0;
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		wait(NULL);
		str = get_next_line(STDIN_FILENO);
		if (str == NULL || ft_strncmp(new_lim, str,
				ft_strlen(new_lim) + 1) == 0)
			break ;
		write(temp_fd, str, ft_strlen(str));
		free(str);
		i++;
	}
	if (str)
		free(str);
	else
		print_error_heredoc(limiter, i);
	return (free(new_lim), 0);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @param limiter: string with the limiter for the here_doc.
 * @param temp_fd: fd from the here_doc file.
 * @brief forks the proces to handle the right signals and get the input
 * for here_doc.
 * @return returns 1 by failure and 0 by success.
*/

static int	fork_here_doc(t_mini *mini, char *limiter, int temp_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (ft_error(NULL, "fork", NULL, 0), 1);
	else if (pid == 0)
	{
		signal(SIGINT, handle_heredoc);
		signal(SIGQUIT, handle_heredoc);
		get_next_line_input(limiter, temp_fd);
		free_all(mini);
		exit (0);
	}
	else
	{
		signal(SIGINT, handle_heredoc_parent);
		signal(SIGQUIT, handle_heredoc_parent);
	}
	wait(NULL);
	close (temp_fd);
	signal(SIGINT, handle_signals);
	if (signal(SIGQUIT, SIG_IGN))
		add(0);
	return (0);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @brief creates an here_doc file and saves it in mini.
 * @return returns 1 by failure and 0 by success.
*/
static int	get_here_doc(t_mini *mini)
{
	t_lex	*current;

	current = mini->lex;
	while (current->sort != HERE_DOC)
		current = current->next;
	current->sort = -1;
	mini->check.here_doc = open("include/here_doc.txt",
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (mini->check.here_doc == -1)
		return (ft_error(NULL, "include/here_doc.txt", NULL, 0), 1);
	if (fork_here_doc(mini, current->str, mini->check.here_doc))
		return (1);
	mini->check.here_doc = open("include/here_doc.txt", O_RDONLY);
	if (mini->check.here_doc == -1)
	{
		if (unlink("include/here_doc.txt") == -1)
			ft_error(NULL, "unlink here_doc", NULL, 0);
		return (ft_error(NULL, "include/here_doc_fd", NULL, 0), 0);
	}
	return (0);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @param lexer: pointer to the lex with infile name (l_lex).
 * @brief checks if the user has access to the given infile.
 * @return returns -1 when the file is not readable, 0 
 * when open() fails and > 0 with the fd nr. 
*/
static int	get_infile(t_mini *mini, t_lex *lexer)
{
	if (access(lexer->str, R_OK) == -1)
		return (ft_error(NULL, lexer->str, NULL, 0), -1);
	mini->check.infile = open(lexer->str, O_RDONLY);
	if (mini->check.infile == -1)
		ft_error(NULL, lexer->str, NULL, 0);
	return (mini->check.infile);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @brief checks sort type infile and here_doc.
 * @return by succes 0, by malloc fail 1.
*/
int	get_input(t_mini *mini)
{
	t_lex	*current;

	current = mini->lex;
	while (current != NULL)
	{
		if (current->sort == INFILE)
		{
			mini->check.infile = get_infile(mini, current);
			mini->in = mini->check.infile;
		}
		else if (current->sort == HERE_DOC)
		{
			if (get_here_doc(mini))
				return (1);
			current->sort = INFILE;
			mini->in = mini->check.here_doc;
		}
		current = current->next;
	}
	return (0);
}
