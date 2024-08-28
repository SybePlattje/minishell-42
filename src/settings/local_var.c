/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:15:29 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/19 08:56:27 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param mini: pointer to all the data (t_mini).
 * @param str: string that contains the name and value of a variable.
 * @param len: size of the name of the variable.
 * @brief search through the local variables to replace the input.
 * @return returns 0 by success and 1 by malloc failure. 
*/
static int	set_local_var(t_mini *mini, char *str, int len)
{
	t_var	*new;
	t_var	*current;

	current = mini->local;
	while (current != NULL)
	{
		if (ft_strncmp(str, current->value, len) == 0)
		{
			free(current->value);
			current->value = ft_strdup(str);
			if (!current->value)
				return (ft_error(NULL, "local var", NULL, 0), 1);
			return (0);
		}
		current = current->next;
	}
	new = new_var(str);
	if (!new)
		return (ft_error(NULL, "local var", NULL, 0), 1);
	var_add_back(mini->local, new);
	return (0);
}

static int	get_var_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @brief search through the local variables to add the input.
 * @return returns 0 by success and 1 by malloc failure. 
*/
int	check_local_var(t_mini *mini)
{
	t_parse	*current;
	int		len;

	current = mini->token;
	while (current != NULL)
	{
		if (current->sort == 0 && current->argv[0][0] != '='
			&& ft_strchr(current->argv[0], '=') != NULL)
		{
			current->sort = -1;
			len = get_var_len(current->argv[0]);
			if (!mini->local)
			{
				mini->local = new_var(current->argv[0]);
				if (!mini->local)
					return (1);
			}
			else if (set_local_var(mini, current->argv[0], len))
				return (1);
		}
		current = current->next;
	}
	return (0);
}

/**
 * @param mini: pointer to all the data (t_mini).
 * @param str: string that contains the name and value of a variable.
 * @brief search through the local variables for the right output.
 * @return returns a string with right value when search for $VAR, 
 * returns NULL by malloc fail. 
*/
char	*check_locals(t_mini *mini, char *str)
{
	t_var	*var;
	char	*temp;
	int		i;

	if (!mini->local)
		return (NULL);
	var = mini->local;
	while (var != NULL)
	{
		if (ft_strncmp(var->value, str, ft_strlen(str)) == 0)
		{
			i = 0;
			while (var->value && var->value[i] != '=')
				i++;
			if (var->value[i] == '\0' || var->value[i + 1] == '\0')
				return (NULL);
			temp = ft_substr(var->value, i + 1,
					ft_strlen(var->value) - (i + 1));
			if (!temp)
				return (ft_error(NULL, "temp", NULL, 0), NULL);
			return (temp);
		}
		var = var->next;
	}
	return (NULL);
}
