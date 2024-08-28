/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:47:40 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/19 14:03:44 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param str: path name that is found for the command.
 * @param str2: relative path name that is given in the input.
 * @brief checks if the relative pathname matches the founded pathname.
 * @return returns 1 if they match, 0 if not.
*/
static int	compare_last_part(char *str, char *str2)
{
	int	i;

	if (ft_strlen(str) < ft_strlen(str2))
	{
		i = ft_strlen(str2) - ft_strlen(str);
		while (*str && str2[i])
		{
			if (*str != str2[i])
				return (0);
			i++;
			str++;
		}
	}
	else
	{
		i = ft_strlen(str) - ft_strlen(str2);
		while (*str2 && str[i])
		{
			if (*str2 != str[i])
				return (0);
			i++;
			str2++;
		}
	}
	return (1);
}

/**
 * @param envp: double pointer to the folder of bash.
 * @param rel_path: string with the relative path.
 * @param cmd: string with the current command.
 * @brief search through all the folders to find the correct program
 * in bash for executing the command and checks if the relative path
 * agrees.
 * @return returns the path to the file, NULL when the command is not found.
*/
char	*pathfinder_abs(char **envp, char *rel_path, char *cmd)
{
	char	*temp;
	char	*path;

	while (*envp)
	{
		temp = ft_strjoin(*envp, "/");
		if (!temp)
			return (ft_error(NULL, "temp", NULL, 0), NULL);
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (!path)
			return (ft_error(NULL, "path", NULL, 0), NULL);
		if (access(path, 0) == 0 && compare_last_part(path, rel_path))
			return (path);
		free(path);
		envp++;
	}
	ft_error(NULL, cmd, ": No such file or directory\n", 127);
	return (NULL);
}

/**
 * @param mini pointer to all the data (t_mini).
 * @param cmd string with the command.
 * @param stop pointer to stop flag for not going in execve.
 * @brief checks whith error to print, wrong command or deleted path.
 * @return 1 by malloc error and 0 with succes.
*/
static int	path_not_found(t_var *var)
{
	t_var	*current;

	current = var;
	while (current != NULL)
	{
		if (ft_strncmp(current->value, "PATH=", 5) == 0)
			return (0);
		current = current->next;
	}
	return (1);
}

/**
 * @param envp: double pointer to the folder of bash.
 * @param cmd: string with the current command.
 * @brief search through all the folders to find the correct program
 * in bash for executing the command.
 * @return returns the path to the file, NULL when the command is not found.
*/
char	*pathfinder(t_mini *mini, char **envp, char *cmd)
{
	char	*temp;
	char	*path;

	if (path_not_found(mini->var))
		return (ft_error(0, cmd, ": No such file or directory\n", 127), NULL);
	while (*envp)
	{
		temp = ft_strjoin(*envp, "/");
		if (!temp)
			return (ft_error(NULL, "temp", NULL, 0), NULL);
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (!path)
			return (ft_error(NULL, "path", NULL, 0), NULL);
		if (access(path, 0) == 0)
			return (path);
		free(path);
		envp++;
	}
	ft_error(0, cmd, ": command not found\n", 127);
	return (NULL);
}

/**
 * @param envp: double pointer to the enviroment variables.
 * @brief search throught the envp to find the matching PWD=.
 * @return returns the path value or NULL when it does not exist.
*/
char	*find_path(char **envp)
{
	char	*temp;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			temp = ft_strdup(envp[i] + 4);
			return (temp);
		}
		i++;
	}
	return (NULL);
}
