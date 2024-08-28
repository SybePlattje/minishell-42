/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:01:05 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/03/20 07:59:15 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

/**
 * @param tok: pointer to the parser struct (t_parse)
 * @param envp: 2D array of all the environment variables
 * @param mini: pointer to the minishell struct (t_mini)
 * @return returns the path needed to run the child on success. NULL on
 * failure or not exists
 * @brief seaches the path needed to run the child program
*/
static char	*get_cmdpath(t_parse *tok, char **envp, t_mini *mini)
{
	char	*cmd;
	char	*path;
	int		i;

	if (tok->argv[0][0] == '/')
	{
		i = ft_strlen(tok->argv[0]);
		while (tok->argv[0][i] != '/' && i != 0)
			i--;
		cmd = ft_substr(tok->argv[0], i + 1, ft_strlen(tok->argv[0]) - i - 1);
		if (!cmd)
			return (ft_error(NULL, "cmd", NULL, 0), NULL);
		return (pathfinder_abs(mini->envp_path, tok->argv[0], cmd));
	}
	else if (ft_strncmp(tok->argv[0], "./", 2) == 0)
	{
		cmd = find_path(envp);
		if (!cmd)
			return (NULL);
		path = ft_strjoin(cmd, tok->argv[0] + 1);
		if (!path)
			return (ft_error(NULL, "path", NULL, 0), NULL);
		return (path);
	}
	return (pathfinder(mini, mini->envp_path, tok->argv[0]));
}

/**
 * @param mini: pointer to the minishell struct (t_mini)
 * @param token: pointer to the parser struct (t_parse)
 * @param envp: 2D array with all the envirenment variables
 * @param stop: flag to check if it's a child process we can run
 * @return returns the errno of the child process, or 0 on success
 * @brief checks if the command is a child process and executes it if found
*/
static int	check_execve(t_mini *mini, t_parse token, char **envp, int stop)
{
	if (is_in_envp(&token, envp))
	{
		token.cmd_path = get_cmdpath(&token, envp, mini);
		if (!token.cmd_path)
			return (free_split(envp), free_split(token.argv), 1);
	}
	else
	{
		ft_error(NULL, token.argv[0], ": No such file or directory\n", 127);
		stop = 1;
	}
	free_split(mini->envp_path);
	free_var(mini->var);
	free_parse(mini);
	if (ft_strcmp(token.argv[0], "") == 0)
		return (add(0), 1);
	if (stop == 0)
		add(execve(token.cmd_path, token.argv, envp));
	if (stop == 0)
		ft_error(0, token.argv[0], 0, 0);
	free(token.cmd_path);
	return (free_split(token.argv), 1);
}

/**
 * @param mini: pointer to the minishell struct (t_mini)
 * @brief sets the in- and output file to there new values
*/
static void	dup_all(t_mini *mini)
{
	if (mini->in == mini->check.infile && mini->in != STDIN_FILENO)
	{
		dup2(mini->in, STDIN_FILENO);
		close(mini->in);
	}
	else if (mini->in != STDIN_FILENO)
		dup2(mini->in, STDIN_FILENO);
	if (mini->out != STDOUT_FILENO)
		dup2(mini->out, STDOUT_FILENO);
}

/**
 * @param mini: pointer to the minishell struct (t_mini)
 * @param token: pointer to the parser struct (t_parse)
 * @return returns the errno, or 0 on success
 * @brief prepares the data needed to go into the child process
*/
int	child_proces(t_mini *mini, t_parse *token)
{
	t_parse	new;
	char	**envp;

	if (mini->in != -1 && mini->out != -1)
	{
		dup_all(mini);
		if (mini->check.pipes)
			close_pipes(mini);
		envp = make_copy_envp(mini->var, 0, 0);
		if (!envp)
			return (1);
		new = make_copy_parse(token);
		if (new.argv[0] == NULL)
			return (free_split(envp), 1);
		free_parse(mini);
		if (check_execve(mini, new, envp, 0))
			return (g_exit_code);
	}
	return (1);
}
