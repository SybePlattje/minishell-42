/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:21:06 by splattje          #+#    #+#             */
/*   Updated: 2024/03/19 13:24:31 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param head: pointer to the environment variable struct (t_var)
 * @param pwd: the current
 * @return retuns 1 on fail, 0 on sucess
 * @brief if PWD= was unset, it is resets it to the current pwd.
*/
int	pwd_not_found(t_var *head, char *pwd)
{
	t_var	*new;
	char	*full_path;

	full_path = ft_strjoin("PWD=", pwd);
	if (full_path == NULL)
		return (ft_error(NULL, "strjoin", NULL, 0), 1);
	new = new_var(full_path);
	if (new == NULL)
		return (1);
	head = var_add_back(head, new);
	return (0);
}

/**
 * @param head: pointer to the variable struct (t_var)
 * @param token: pointer to the parser struct (t_parse)
 * @return returns -1 on malloc error or if it isn't used, 1 on soft error,
 * 0 on success
*/
int	goto_old_pwd(t_var *head, t_parse *token)
{
	char	*full_path;
	t_var	*current;

	if (ft_strcmp(token->argv[1], "-") == 0 && ft_strlen(token->argv[1]) == 1)
	{
		current = head;
		while (current != NULL)
		{
			if (ft_strncmp(current->value, "OLDPWD=", 7) == 0)
			{
				full_path = ft_strdup(current->value + 7);
				if (full_path == NULL)
					return (ft_error(NULL, "strdup", NULL, 0), -1);
				chdir(full_path);
				if (change_envp_dir(full_path, head, 1))
					return (1);
				return (0);
			}
			current = current->next;
		}
		if (current == NULL)
			return (ft_error("minishell: ", "cd: ", "OLDPWD not set\n", 1), 0);
	}
	return (-1);
}
