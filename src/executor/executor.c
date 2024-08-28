/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:27:56 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/19 14:33:45 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param mini: pointer to the minishell struct (t_mini)
 * @param token: pointer to the parser struct (t_parse)
 * @param var: pointer to the environment variables (t_var)
 * @param i: pointer to index
 * @return returns the return value based on the buildin or -1 if there
 * are none
 * @brief based on the word in token->argv[0] executes different buildins
*/
static int	check_builtins(t_mini *mini, t_parse *token, t_var *var, int *i)
{
	int	return_value;

	return_value = -1;
	if (ft_strcmp("echo", token->argv[0]) == 0)
		return_value = print_echo(mini, token);
	else if (ft_strcmp("cd", token->argv[0]) == 0)
		return_value = cd(token, mini->var);
	else if (ft_strcmp("pwd", token->argv[0]) == 0)
		return_value = print_pwd(mini);
	else if (ft_strcmp("export", token->argv[0]) == 0)
		return_value = print_export(mini, token->argv[1], token);
	else if (ft_strcmp("env", token->argv[0]) == 0)
		return_value = print_environment(mini, var);
	else if (ft_strcmp("unset", token->argv[0]) == 0)
		return_value = unset_env_var(token, var);
	else if (ft_strcmp("exit", token->argv[0]) == 0)
		return_value = get_exit_code(token);
	if (return_value != -1)
		close_in_out(mini);
	if (return_value == -1)
		i[0]++;
	return (return_value);
}

/**
 * @param mini: pointer to the minishell struct (t_mini)
 * @param token: pointer to the parser struct (t_parse)
 * @return returns 0 or 1 if process is successfull
 * @brief it creates a new process and checks if everything goes well
*/
static int	forking(t_mini *mini, t_parse *token)
{
	pid_t	pid;
	int		return_value;

	pid = fork();
	if (pid < 0)
	{
		close_pipes(mini);
		return (ft_error(NULL, "fork", NULL, 0), 1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, handle_signals_child);
		signal(SIGQUIT, handle_signals_child);
		return_value = child_proces(mini, token);
		exit (return_value);
	}
	else
	{
		signal(SIGINT, handle_signal_parent);
		signal(SIGQUIT, handle_signal_parent);
		close_in_out(mini);
	}
	return (0);
}

/**
 * @param mini: pointer to the minishell struct (t_mini)
 * @param previous: pointer to the previous parser (t_parse)
 * @param current: pointer to teh current parser (t_parse)
 * @return retuns 1 in case of handeling infile, 0 if not
 * @brief handles mini->in and mini->out after infile
*/
int	check_previous(t_mini *mini, t_parse *previous, t_pipe *current)
{
	if (previous->sort == INFILE)
	{
		close(current->pipe[WRITE]);
		mini->in = current->pipe[READ];
		if (mini->check.pipes == current->nr + 1 && mini->check.outfile == 0)
			mini->out = STDOUT_FILENO;
		else if (mini->check.pipes == current->nr + 1
			&& mini->check.outfile)
			mini->out = mini->check.outfile;
		else
		{
			if (current->next == NULL)
			{
				if (mini->check.outfile)
					mini->out = mini->check.outfile;
				else
					mini->out = STDOUT_FILENO;
			}
			else
				mini->out = current->next->pipe[WRITE];
		}
		return (1);
	}
	return (0);
}

/**
 * @param mini: pointer to the minishell struct (t_mini)
 * @param token: pointer to current token (t_parse)
 * @param prev: pointer to the previous token (t_parse)
 * @param round: if start with pipe, close pipe.
 * @brief searches to right output fd or pipe or outfile
*/
static void	get_in_out(t_mini *mini, t_parse *token, t_parse *prev, int round)
{
	t_pipe	*current;

	current = mini->pipe;
	while (current && current->nr != token->pipe_nr)
		current = current->next;
	if (round == 0)
	{
		close(current->pipe[0]);
		close(current->pipe[1]);
	}
	else
	{
		if (check_previous(mini, prev, current))
			return ;
		mini->in = current->pipe[READ];
	}
	if (current->next == NULL)
	{
		if (mini->check.outfile)
			mini->out = mini->check.outfile;
		else
			mini->out = STDOUT_FILENO;
	}
	else
		mini->out = current->next->pipe[WRITE];
}

/**
 * @param mini pointer the the minishell struct (t_mini)
 * @param i: integer that is set to 0 for counting commands.
 * @param round: amount of commands that are passed.
 * @return returns non 0 based on user input, 0 if it's something we can't
 * do anything with
 * @brief checks if the token in mini is a buildin, or a child process
*/
int	executor(t_mini *mini, int i, int round)
{
	t_parse	*current;
	t_parse	*previous;
	int		return_value;

	current = mini->token;
	previous = NULL;
	while (current != NULL)
	{
		if (current->sort == 0 && current->argv)
		{
			round++;
			return_value = check_builtins(mini, current, mini->var, &i);
			if (return_value == -1)
				forking(mini, current);
			else if (return_value != 0)
				return (return_value);
		}
		else if (current->sort == PIPE)
			get_in_out(mini, current, previous, round);
		previous = current;
		current = current->next;
	}
	wait_for_child(i);
	return (signal(SIGQUIT, SIG_IGN), 0);
}
