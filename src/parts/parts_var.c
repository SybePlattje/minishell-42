/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parts_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:05:55 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/19 08:18:47 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

/**
 * @param i: integer that is the lenght untill the = sign.
 * @param str: string that include the dollar sign, is NULL when
 * the var is $?.
 * @param r_value: a pointer that becomes 1 by malloc failure.
 * @brief makes the new string with the value of the variable.
 * @return returns the new string or NULL by failure.
*/
static char	*malloc_var(int i, char *str, int *r_value)
{
	char	*new;

	if (str == NULL)
		new = ft_itoa(g_exit_code);
	else
		new = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (!new)
	{
		ft_error(NULL, "new", NULL, 0);
		r_value[0] = 1;
		return (NULL);
	}
	return (new);
}

/**
 * @param value: a string with the found variable value.
 * @param str: string that include the dollar sign.
 * @brief compares the variable name with all the saved variables.
 * @return returns 1 if there is a match, else 0.
*/
static int	check_varname(char *value, char *str)
{
	int	len;
	int	strl;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
	{
		if (str[len] == '=')
			break ;
		len++;
	}
	strl = ft_strlen(str);
	if (ft_strncmp(value, str, len - 1) == 0 && (value[strl] == '\0'
			|| value[strl] == '=' || str[strl - 1] == '}'))
		return (1);
	return (0);
}

/**
 * @param mini: pointer that contains all the data (t_mini).
 * @param str: string that include the dollar sign.
 * @param brackets: place to store if there are brackets in the str.
 * @param r_value: pointer to a return value by error.
 * @brief search for a match of a variable name and the saved variables.
 * @return returns the new string, or NULL by error.
*/
static char	*search_var(t_mini *mini, char *str, int brackets, int *r_value)
{
	int		i;
	int		len;
	t_var	*var;

	brackets = check_brackets(str);
	len = ft_strlen(str);
	if (brackets)
		str++;
	if (brackets)
		len -= 3;
	if (str[0] == '?')
		return (malloc_var(0, NULL, r_value));
	var = mini->var;
	while (var != NULL)
	{
		i = 0;
		if (var->value && check_varname(var->value, str))
		{
			while (var->value[i] != '=')
				i++;
			return (malloc_var(i, var->value, r_value));
		}
		var = var->next;
	}
	return (check_locals(mini, str));
}

/**
 * @param mini: pointer that contains all the data (t_mini).
 * @param r_value: pointer to a return value by error.
 * @brief checks by all lexers if there is a part that contains a
 * dollar sign and if the variablename has to change to the value.
 * @return returns 0 by success, and 1 by error.
*/
int	handle_var(t_mini *mini, int *r_value)
{
	t_lex	*lexer;
	t_parts	*part;
	char	*temp;

	lexer = mini->lex;
	while (lexer != NULL)
	{
		part = lexer->parts;
		while (part != NULL)
		{
			if (part->keep == 1 && ft_strchr(part->str, '$') != NULL
				&& ft_strlen(part->str) > 1)
			{
				temp = search_var(mini, part->str + 1, 0, r_value);
				if (!temp)
					return (1);
				free(part->str);
				part->str = temp;
			}
			part = part->next;
		}
		lexer = lexer->next;
	}
	return (0);
}

/**
 * @param envp: double pointer that contains all the envp.
 * @brief changes the envp from double pointer to a linked list.
 * @return returns the head of the linked list or NULL by failure.
*/
t_var	*set_var(char **envp)
{
	t_var	*head;
	size_t	index;
	t_var	*current;

	head = NULL;
	index = -1;
	while (envp[++index] != NULL)
	{
		current = new_var(envp[index]);
		if (current == NULL)
		{
			if (index > 0)
			{
				free_var(head);
				return (NULL);
			}
		}
		if (head == NULL)
			head = current;
		else
			head = var_add_back(head, current);
	}
	return (head);
}
