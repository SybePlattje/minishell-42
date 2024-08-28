/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:13:17 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/06/28 21:37:37 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param pwd: string holding the old current working directory
 * @param envp: pointer to the variables struct (t_var)
 * @return retuns non 0 if error happens, 0 if everything went well
 * @brief save the OLDPWD to where we were. 
*/
static int	save_oldpwd(char *pwd, t_var *envp)
{
	t_var	*var;

	var = envp;
	while (var != NULL)
	{
		if (var->value && ft_strncmp(var->value, "OLDPWD=", 7) == 0)
		{
			free(var->value);
			var->value = ft_strjoin("OLD", pwd);
			if (!var->value)
				return (ft_error(NULL, "oldvar", NULL, 0), 1);
			return (0);
		}
		var = var->next;
	}
	return (0);
}

/**
 * @param full_path: string that contais the full path of where we want to go to.
 * @param envp: pointer to the variables struct (t_var)
 * @param option flag to check if full_path needs to be freed or not
 * @brief if the current envp is PWD= than change old pwd to the new one
 * in full_path
 * @return returns 1 if error occured, 0 if everything went well.
*/
int	change_envp_dir(char *full_path, t_var *envp, int option)
{
	t_var	*current;
	int		found;

	current = envp;
	found = 0;
	while (current != NULL)
	{
		if (ft_strncmp(current->value, "PWD=", 4) == 0)
		{
			if (save_oldpwd(current->value, envp))
				return (1);
			free(current->value);
			current->value = ft_strjoin("PWD=", full_path);
			if (!current->value)
				return (ft_error(NULL, "current->value", NULL, 0), 1);
			found = 1;
		}
		current = current->next;
	}
	if (found == 0)
		if (pwd_not_found(envp, full_path))
			return (1);
	if (option == 1)
		free(full_path);
	return (0);
}

/**
 * @param token: pointer to the parser struct (t_parse)
 * @param envp: pointer to the variables struct (t_var)
 * @return returns non null if error occured, 0 if everything went well, and
 * -1 if token->argv[1] doesn't equal ~/
 * @brief changes the direntory to home if token->argv[1] is ~/
*/
static int	home_dir(t_parse *token, t_var *envp)
{
	t_var	*current;
	char	*full_path;
	char	*str;

	str = token->argv[1];
	if (str == NULL || ft_strcmp(str, "~/") == 0)
	{
		current = envp;
		while (current != NULL)
		{
			if (ft_strncmp(current->value, "HOME=", 5) == 0)
			{
				full_path = ft_strdup(current->value + 5);
				if (full_path == NULL)
					return (ft_error(NULL, "strdup", NULL, 0), -1);
			}
			current = current->next;
		}
		chdir(full_path);
		if (change_envp_dir(full_path, envp, 1))
			return (1);
		return (0);
	}
	return (-1);
}

/**
 * @param token: pointer to the parser struct (t_parse)
 * @param envp: pointer to the variables struct (t_var)
 * @return returns non 0 if error occured, 0 if everythig went well
 * @brief changes the directory to the one thats given by the user.
*/
static int	change_directory(t_parse *token, t_var *envp)
{
	char	full_path[PATH_MAX];

	if (chdir(token->argv[1]) == -1)
		return (ft_error("cd: ", token->argv[1], NULL, 0), 0);
	getcwd(full_path, PATH_MAX);
	if (!full_path[0])
		return (ft_error(NULL, "full_path", NULL, 0), 1);
	if (change_envp_dir(full_path, envp, 2))
		return (1);
	return (0);
}

/**
 * @param token: pointer to the parser struct (t_parse) 
 * @param envp: pointer to the stuct that holds the envirenment variables (t_var)
 * @return returns non 0 if an error occured, if everything went well it
 * returns 0
 * @brief changes the current directory.
*/
int	cd(t_parse *token, t_var *envp)
{
	int	r_value;

	if (check_amount_dir(token))
		return (0);
	r_value = home_dir(token, envp);
	if (r_value != -1)
		return (r_value);
	r_value = goto_old_pwd(envp, token);
	if (r_value != -1)
		return (r_value);
	if (change_directory(token, envp))
		return (1);
	return (0);
}
