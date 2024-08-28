/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:28:37 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/06/28 21:36:06 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param mini: pointer to all the data (t_mini).
 * @brief closes pipes by fork error or in the childproces.
*/
void	close_pipes(t_mini *mini)
{
	t_pipe	*current;

	if (!mini->pipe)
		return ;
	current = mini->pipe;
	while (current != NULL)
	{
		if (close(current->pipe[READ]) == -1)
			add(errno);
		if (close(current->pipe[WRITE]) == -1)
			add(errno);
		current = current->next;
	}
}

static t_pipe	*new_pipe(int nr)
{
	t_pipe	*new;

	new = (t_pipe *)malloc(sizeof(t_pipe));
	if (new == NULL)
		return (ft_error(NULL, "new pipe", NULL, 0), NULL);
	new->nr = nr;
	if (pipe(new->pipe) == -1)
	{
		free(new);
		return (ft_error(NULL, "pipe", NULL, 0), NULL);
	}
	new->next = NULL;
	return (new);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @brief creates the right amount of pipe structs.
 * @return returns 0 by success,  and 1 by malloc of pipe fault. 
*/
int	set_pipes(t_mini *mini)
{
	int		pipe;
	t_pipe	*current;

	mini->pipe = new_pipe(0);
	if (!mini->pipe)
		return (1);
	pipe = 1;
	current = mini->pipe;
	while (pipe < mini->check.pipes)
	{
		current->next = new_pipe(pipe);
		if (current->next == NULL)
			return (1);
		pipe++;
		current = current->next;
	}
	if (mini->check.pipes)
		mini->out = mini->pipe->pipe[WRITE];
	else
		mini->out = STDOUT_FILENO;
	return (0);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @brief checks for double pipes
 * @return returns 0 by success,  and 1 by double pipe. 
*/
int	check_pipes(t_mini *mini)
{
	t_lex	*lex;
	int		pipe;
	char	*string;

	lex = mini->lex;
	pipe = 0;
	while (lex != NULL)
	{
		if (lex->sort == PIPE)
		{
			if (pipe == 1)
			{
				string = "syntax error near unexpected token";
				ft_error("minishell: ", string, NULL, 1);
				ft_putstr_fd(" `|'\n", 2);
				return (1);
			}
			pipe = 1;
		}
		else
			pipe = 0;
		lex = lex->next;
	}
	return (0);
}
