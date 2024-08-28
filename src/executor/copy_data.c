/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:23:52 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/20 07:58:35 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param argv: double pointer to the enviroment variables.
 * @param i: amount of strings for double pointer.
 * @return double pointer with copy of argv.
 * @brief makes a copy of the existing argv for parsing.
*/
static char	**make_argv_copy(char **argv, int i)
{
	char	**copy;

	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (ft_error(NULL, "copy", NULL, 0), NULL);
	i = 0;
	while (argv[i])
	{
		copy[i] = ft_strdup(argv[i]);
		if (!copy[i])
		{
			ft_error(NULL, "*copy", NULL, 0);
			while (i)
			{
				if (copy[i])
					free(copy[i]);
				i--;
			}
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

/**
 * @param token: pointer to parser (t_parse).
 * @return pointer to copy of parser (t_parse).
 * @brief copies the information from the current token
 * to a copy before removing all the tokens.
*/
t_parse	make_copy_parse(t_parse *token)
{
	t_parse	new;
	int		i;

	new.cmd_path = NULL;
	i = 0;
	while (token->argv[i])
		i++;
	new.argv = make_argv_copy(token->argv, i);
	if (!new.argv)
		return (new);
	return (new);
}

/**
 * @param var: pointer to all the variables (t_var).
 * @param len: amount of var pointers in linked list.
 * @return double pointer with the variables.
 * @brief takes the variables in var and puts them in
 * a double pointer.
*/
char	**make_copy_envp(t_var *var, int len, int i)
{
	t_var	*current;
	char	**envp;

	current = var;
	while (current != NULL)
	{
		len++;
		current = current->next;
	}
	envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (ft_error(NULL, "envp", NULL, 0), NULL);
	while (var != NULL && i < len)
	{
		envp[i] = ft_strdup(var->value);
		if (!envp[i])
			return (ft_error(NULL, "envp", NULL, 0), free_split(envp), NULL);
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0 && ft_strlen(envp[i]) >= 7)
			envp[i][6] += 1;
		i++;
		var = var->next;
	}
	envp[i] = NULL;
	return (envp);
}
