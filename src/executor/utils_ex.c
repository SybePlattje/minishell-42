/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:27:49 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/13 09:44:21 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param mini: pointer to all the data (t_mini).
 * @brief closes the mini->in & mini->out.
*/
void	close_in_out(t_mini *mini)
{
	if (close(mini->in) == -1)
		add(errno);
	if (mini->out != STDOUT_FILENO)
	{
		if (close(mini->out) == -1)
			add(errno);
	}
}

/**
 * @param str1: string with the command.
 * @param str2: string of the current envp.
 * @param len: len of the command.
 * @brief compares two strings from the end.
 * @return 0 if they are the same, 1 if not.
*/
static int	ft_strncmp_back(char *str1, char *str2, int len)
{
	int	i;
	int	j;

	i = ft_strlen(str2) - len;
	if (i < 1)
		return (1);
	j = 0;
	while (str1[j])
	{
		if (str1[j] != str2[i])
			return (1);
		i++;
		j++;
	}
	return (0);
}

/**
 * @param token: pointer to current token (t_parse).
 * @param envp: double pointer to environment variables.
 * @brief checks if the command is in the envp, than  it is not
 * a command.
 * @return 0 when it is a envp variable and 1 if it is not.
*/
int	is_in_envp(t_parse *token, char **envp)
{
	int	i;
	int	len;
	int	len2;

	i = 0;
	len = ft_strlen(token->argv[0]);
	while (envp[i])
	{
		if (!ft_strncmp_back(token->argv[0], envp[i], len))
		{
			len2 = ft_strlen(envp[i]) - len;
			if (envp[i][len2] == '/')
				return (0);
		}
		i++;
	}
	return (1);
}

/**
 * @param i: amount of childs that are made.
 * @brief waits till all the children are ready and saves 
 * the status in de g_exit_code.
*/
void	wait_for_child(int i)
{
	int	status;

	while (i)
	{
		i--;
		wait(&status);
		if (WIFEXITED(status))
			add(WEXITSTATUS(status));
	}
}
