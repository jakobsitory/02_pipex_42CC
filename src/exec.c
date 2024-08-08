/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:13:45 by jschott           #+#    #+#             */
/*   Updated: 2024/08/08 11:09:29 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/**
 * Frees a dynamically allocated array of strings.
 * 
 * @param arr The array of strings to be freed.
 * @return Always returns 1, indicating successful deallocation of the array and its contents.
 */
int	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (1);
}

/**
 * Retrieves the executable path for a command.
 * 
 * @param cmd The command for which to find the executable path.
 * @param env The environment variables array, where the PATH variable can be found.
 * @return The executable path if found, otherwise NULL.
 */
char	*get_exec_path(char *cmd, char **env)
{
	char	**path_split;
	int		i;
	char	*path_complete;
	char	*exec_path;

	path_split = 0;
	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH", 4))
		i++;
	path_split = ft_split(ft_strchr(env[i], '/'), ':');
	i = -1;
	while (path_split[++i])
	{
		path_complete = ft_strjoin(path_split[i], "/");
		exec_path = ft_strjoin(path_complete, cmd);
		free (path_complete);
		if (access(exec_path, X_OK | F_OK) == 0)
		{
			free_str_arr (path_split);
			return (exec_path);
		}
		free (exec_path);
	}
	free_str_arr (path_split);
	return (0);
}

/**
 * Executes a command with the provided environment variables.
 * 
 * @param cmd The command string to be executed.
 * @param env The environment variables array.
 * @return -1 if the command cannot be executed, otherwise it does not return.
 */
int	exec(char *cmd, char **env)
{
	char	**cmd_flags;
	char	*exec_path;

	cmd_flags = ft_split(cmd, ' ');
	if (!cmd_flags)
		return (-1);
	exec_path = get_exec_path(cmd_flags[0], env);
	if (!exec_path)
		exec_path = cmd_flags[0];
	if (execve(exec_path, cmd_flags, env) == -1)
	{
		free_str_arr(cmd_flags);
		error_mgmt(CMMND_ERR, cmd);
	}
	free_str_arr (cmd_flags);
	if (!exec_path)
		error_mgmt(CMMND_ERR, cmd);
	return (1);
}
