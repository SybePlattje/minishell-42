/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:19:23 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/20 07:57:32 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_exit_code;

/**
 * @param nr: errno or signal number
 * @brief adds the return number to the global exit_code
*/
void	add(int nr)
{
	if (nr > 255)
		nr %= 256;
	g_exit_code = nr;
}

/**
 * @param mini: pointer to the minishell struct (t_mini)
 * @param line: the current line the user inputted
 * @return retuns 0 on success, non 0 of failure
 * @brief initializes the lexer, parser, local variables, checkes for pipes.
*/
static int	program(t_mini *mini, char *line, int exit_value)
{
	if (first_checks(line))
		return (exit_value);
	exit_value = lexer(mini, line);
	if (exit_value != 0)
		return (exit_value);
	if (check_pipes(mini))
		return (0);
	exit_value = settings(mini);
	if (exit_value != 0)
		return (exit_value);
	exit_value = parser(mini);
	if (exit_value != 0)
		return (exit_value);
	if (check_local_var(mini))
		return (1);
	if (mini->check.pipes && set_pipes(mini))
		return (1);
	if (executor(mini, 0, 0))
		return (1);
	clean(mini, exit_value);
	return (0);
}

/**
 * @return string with input line
 * @brief takes input with readline and trims on spaces and tabs.
*/
char	*read_line(void)
{
	char	*line;
	char	*new_line;

	while (1)
	{
		line = readline("\033[1;36mminishell:\033[0m ");
		if (!line)
			return (NULL);
		if (empty_line(line))
		{
			new_line = ft_strtrim((char *)line, " \t");
			free(line);
			if (!new_line)
				return (ft_error(NULL, "new_line", NULL, 0), NULL);
			return (new_line);
		}
		free(line);
	}
}

/**
 * @param mini: pointer to the minishell struct (t_mini)
 * @return retuns 0 when done
 * @brief starts a promts and reads the line the user inputs.
*/
static int	start_program(t_mini *mini, int exit_value)
{
	char	*line;

	if (signal(SIGQUIT, SIG_IGN))
		add(0);
	while (1)
	{
		signal(SIGINT, handle_signals);
		line = read_line();
		if (!line)
			break ;
		add_history(line);
		line = check_last_pipe(line, &exit_value);
		if (exit_value == 1 || program(mini, line, 0) == 1)
			break ;
		if (line)
			free(line);
		wait (NULL);
	}
	if (line)
		free(line);
	return (0);
}

/**
 * @param argc: amount of arguments given at program startup
 * @param argv: the arguments given at program startup
 * @param envp: 2D array of the envionment variables
 * @return retuns the exit code based on what happens in the shell
 * @brief initializes the minishell struct (t_mini) and make everything
 * ready for use
*/
int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;

	mini = (t_mini *)malloc(sizeof(t_mini));
	if (!mini)
		return (ft_error(0, "mini", 0, 0), errno);
	if (memset_all(mini, argc, argv))
		return (g_exit_code);
	mini->var = set_var(envp);
	if (!mini->var)
		return (g_exit_code);
	if (get_paths(mini, mini->var))
		return (g_exit_code);
	start_program(mini, 0);
	free_all(mini);
	return (g_exit_code);
}

//  ANSI Escape Codes
/*
\033 (octale notatie) = escapecode waar ANSI escape codes vaak mee beginnen
\033[30m tot \033[37m = kleurcode aanpassen		\033[1m: Vetgedrukte tekst.
\033[0m: Herstelt alle opmaak naar de standaardinstellingen.
line = readline("\033[1;36mminishell:\033[0m ");
*/