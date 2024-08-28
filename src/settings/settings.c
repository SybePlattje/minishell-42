/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:03:09 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/12 14:48:08 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param mini: pointer to all the data (t_mini).
 * @brief handle quotes, in - and output.
 * @return returns 0 by success,  and 1 by error.
*/
int	settings(t_mini *mini)
{
	int	return_value;

	return_value = 0;
	if (handle_parts(mini))
		return (1);
	if (handle_var(mini, &return_value) && return_value == 1)
		return (1);
	if (merge_parts(mini, 1))
		return (1);
	if ((mini->check.infile || mini->check.here_doc) && get_input(mini))
		return (1);
	if (mini->check.outfile)
		return (get_output(mini));
	return (0);
}
