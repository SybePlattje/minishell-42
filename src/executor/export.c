/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:56:47 by splattje          #+#    #+#             */
/*   Updated: 2024/03/12 16:13:37 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param head: pointer to the head of the copy of head
 * @param new: pointer to the variable struct (t_var) with the new variable
 * needed to be sorted in head
 * @brief sorts the new variable in the head based on alphabetical order
*/
static void	sorted_insert(t_var **head, t_var *new)
{
	t_var	*current;

	if (*head == NULL || ft_strcmp((*head)->value, new->value) >= 0)
	{
		new->next = *head;
		*head = new;
	}
	else
	{
		current = *head;
		while (current->next != NULL
			&& ft_strcmp(current->next->value, new->value) < 0)
			current = current->next;
		new->next = current->next;
		current->next = new;
	}
}

/**
 * @param head: pointer to the start of the variable struct (t_var)
 * @return returns a sorted variable pointer head on success, on failure
 * it retuns NULL
 * @brief makes a copy of the head and sorts it.
*/
static t_var	*sort_copy(t_var *head)
{
	t_var	*sorted_var;
	t_var	*current;
	t_var	*new_node;

	sorted_var = NULL;
	current = head;
	while (current != NULL)
	{
		new_node = new_var(current->value);
		if (new_node == NULL)
		{
			free_var(sorted_var);
			return (NULL);
		}
		sorted_insert(&sorted_var, new_node);
		current = current->next;
	}
	return (sorted_var);
}

/**
 * @param value: the value of the t_var struct
 * @return returns NULL on eerror and a string on success
 * @brief if value contains a '=' everything after it needs to be in quotes
*/
static char	*quotes_for_value(char *value)
{
	char	*equal_pos;
	size_t	length;
	char	*output;
	size_t	prefix_length;

	equal_pos = ft_strchr(value, '=');
	if (equal_pos != NULL)
	{
		length = ft_strlen(value) + 3;
		output = (char *)malloc(length);
		if (output == NULL)
			return (NULL);
		prefix_length = equal_pos - value;
		ft_strncpy(output, value, prefix_length);
		output[prefix_length] = '\0';
		ft_strlcat(output, "=\"", length);
		ft_strlcat(output, equal_pos + 1, length);
		ft_strlcat(output, "\"", length);
		free(value);
		return (output);
	}
	else
		return (value);
}

/**
 * @param sorted_var: pointer to variables struct (t_var)
 * @param fd_out: the fd of the output
 * @return returns not 0 on error, 0 if everything went well
 * @brief sorts the envirment and prints them out
*/
static int	output_export(t_var *sorted_var, int fd_out)
{
	t_var	*tmp;

	while (sorted_var != NULL)
	{
		tmp = sorted_var->next;
		ft_putstr_fd("declare -x ", fd_out);
		sorted_var->value = quotes_for_value(sorted_var->value);
		if (sorted_var->value == NULL)
		{
			free_var(sorted_var);
			return (ft_error(NULL, "malloc for quotes", NULL, 0), errno);
		}
		ft_putendl_fd(sorted_var->value, fd_out);
		free(sorted_var->value);
		free(sorted_var);
		sorted_var = tmp;
	}
	return (0);
}

/**
 * @param mini: pointer to the minishell struct (t_mini)
 * @param str: holds the new variable needed to add
 * @param token: pointer to the parser struct (t_parse)
 * @return returns non 0 if an error occured, 0 if everything went well
 * @brief if str is empty it prints the envirenment variables in alphabetical
 * order. If str isn't empty it checks and adds it to the envirenment variables
*/
int	print_export(t_mini *mini, char *str, t_parse *token)
{
	t_var	*sorted_var;
	int		result;

	result = 0;
	if (str == NULL)
	{
		sorted_var = sort_copy(mini->var);
		result = output_export(sorted_var, mini->out);
	}
	else
		result = check_var(mini->var, token);
	return (result);
}
