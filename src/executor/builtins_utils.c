/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:30:15 by splattje          #+#    #+#             */
/*   Updated: 2024/03/19 14:43:29 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param name: pointer to the name we want to check.
 * @return returns 1 if names are velid 0 if invallid.
 * @brief checks the name doesn't start with a digit, and every other
 * character is alpha or '_'
*/
static int	valid_input(char **name)
{
	size_t	index;

	index = 0;
	while (*name[index] && (*name[index] == '=' && *name[index + 1]))
	{
		if (index == 0 && ft_isdigit(*name[index]))
			return (ft_error(*name, NULL, " not a valid identifier\n", 1),
				free(*name), 0);
		if (!ft_isalnum(*name[index]) || *name[index] != '_')
			return (ft_error(*name, NULL, " not a valid identifier\n", 1),
				free(*name), 0);
		index++;
	}
	return (free(*name), 1);
}

/**
 * @param current: pointer to the variables struct (t_var)
 * @param new_value: string containing the data of the new value
 * @param flag true if the variable already exists, false if it's new
 * @param name pointer to the names of the variable
 * @return returns non 0 if error occurs, 0 if everyting went well
 * @brief if flag is true and new_value contains a '=' update the value to
 * new_value. If flag is true and new_value doesn't contain a '=' we do
 * nothing. Else we add a new variable to current with new_value
*/
static int	update_or_add(t_var *current, char *new_value, int flag,
	char **name)
{
	t_var	*new;

	if (valid_input(name))
	{
		if (flag && ft_strchr(new_value, '=') != 0)
		{
			free(current->value);
			current->value = ft_strdup(new_value);
			if (current->value == NULL)
				return (ft_error(NULL, "current->value malloc", NULL, 0),
					errno);
		}
		else if (flag && ft_strchr(new_value, '=') == 0)
			return (0);
		else
		{
			new = new_var(new_value);
			if (new == NULL)
				return (ft_error(NULL, "new malloc", NULL, 0), errno);
			current->next = new;
		}
	}
	return (0);
}

/**
 * @param value: string with the data for the variable
 * @param var pointer to the variables struct (t_var)
 * @param len the lenght of the new var name
 * @return returns non 0 if error occurs, 0 if everyting went well
 * @brief loops through var and checks if the variable already exists 
*/
static int	write_multi_var(char *value, t_var *var, int len)
{
	t_var	*current;
	char	*name;
	int		found;

	current = var;
	name = ft_substr(value, 0, len);
	if (name == NULL)
		return (ft_error(NULL, "name malloc", NULL, 0), errno);
	found = 0;
	while (1)
	{
		if (ft_strncmp(name, current->value, len) == 0
			&& ((current->value[len] == '\0' || current->value[len] == '=')))
		{
			found = 1;
			break ;
		}
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	if (update_or_add (current, value, found, &name))
		return (errno);
	return (0);
}

/**
 * @param var: pointer to the variables struct (t_var)
 * @param token: pointer to the parser struct (t_parse)
 * @return returens non 0 if error occurs, 0 if everything went well
 * @brief calculates the length of the var name and pushes data to
 * write_multi_var()
*/
int	check_var(t_var *var, t_parse *token)
{
	char	*name;
	int		index;
	int		i;

	index = 1;
	while (token->argv[index] != NULL)
	{
		i = 0;
		name = token->argv[index];
		while (name[i] && name[i] != '=')
			i++;
		if (write_multi_var(name, var, i))
			return (errno);
		index++;
	}
	return (0);
}

/**
 * @param token: pointer to the parser struct (t_parse)
 * @brief checks if there is only one argument in token->argv
 * @return returns 1 if there is more then 1 token->argv, 0 if there is 1
*/
int	check_amount_dir(t_parse *token)
{
	int	i;

	i = 0;
	while (token->argv[i])
		i++;
	if (i > 2)
		return (ft_error("cd: ", NULL, "too many arguments\n", 1), 1);
	return (0);
}
