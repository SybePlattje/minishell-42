/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:25:12 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/19 14:07:29 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	w_error(char *str1, char *str2, char *str3)
{
	ft_error(str1, str2, str3, 2);
	return (1);
}

/**
 * @param token: pointer to argv[1] that contains exitnumber (t_parse).
 * @brief counting the exitnumber after the command 'exit'.
 * @return by succes: 0, by wrong input: 1.
*/
int	get_exit_code(t_parse *token)
{
	long int	nr;
	char		*number;

	if (token->argv[1] == NULL)
		return (1);
	number = token->argv[1];
	while (*number && *number == ' ')
		number++;
	if (*number == '+' || *number == '-')
		number++;
	if (*number == '+' || *number == '-')
		return (w_error("minishell: exit: ", token->argv[1],
				": numeric argument required\n"));
	if (!ft_isdigit(*number))
		return (w_error("minishell: exit: ", token->argv[1],
				": numeric argument required\n"));
	if (token->argv[2] != NULL)
		return (ft_error("minishell: exit: ", "too many arguments\n", 0, 1), 0);
	nr = 0;
	if (!ft_atoi_save(token->argv[1], &nr))
		return (w_error("minishell: exit: ", token->argv[1],
				": numeric argument required\n"));
	return (add(nr), 1);
}

/**
 * @param mini: pointer to access all the data (t_mini).
 * @brief delete everything in mini and history.
*/
int	free_all(t_mini *mini)
{
	rl_clear_history();
	close(mini->save_in);
	close(mini->save_out);
	if (mini->envp_path)
		free_split(mini->envp_path);
	if (mini->token)
		free_parse(mini);
	if (mini->var)
		free_var(mini->var);
	if (mini->lex)
		free_lexer(mini);
	if (mini->pipe)
		free_pipes(mini);
	if (mini->local)
		free_var(mini->local);
	free(mini);
	return (0);
}
