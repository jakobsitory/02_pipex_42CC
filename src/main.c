/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 09:27:10 by jschott           #+#    #+#             */
/*   Updated: 2024/08/08 11:10:06 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/**
 * Writes input from a file to a pipe for processing by a command.
 * 
 * @param cmd The command to execute, which will process the input from the file.
 * @param file_in The path to the input file.
 * @param fd_pipe A pointer to an array containing the file descriptors for the pipe.
 * @param env The environment variables array.
 * @return Returns 1 upon successful execution, or calls `error_mgmt` in case of an error.
 */
int	write_2_pipe(char *cmd, char *file_in, int *fd_pipe, char **env)
{
	int	fd_in;

	fd_in = open(file_in, O_RDONLY);
	if (fd_in <= 0)
		return (error_mgmt(INPUT_ERR, file_in));
	dup2(fd_in, 0);
	dup2(fd_pipe[1], 1);
	close(fd_pipe[0]);
	exec(cmd, env);
	close(fd_in);
	return (1);
}

/**
 * Reads output from a pipe and writes it to a file.
 * 
 * @param cmd The command to execute, which will process the output from the pipe.
 * @param file_out The path to the output file.
 * @param fd_pipe A pointer to an array containing the file descriptors for the pipe.
 * @param env The environment variables array.
 * @return Returns 1 upon successful execution, or calls `error_mgmt` in case of an error.
 */
int	read_pipe(char *cmd, char *file_out, int *fd_pipe, char **env)
{
	int	fd_out;

	wait (NULL);
	fd_out = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_out <= 0)
		return (error_mgmt(OUTPUT_ERR, file_out));
	dup2(fd_out, 1);
	dup2(fd_pipe[0], 0);
	close(fd_pipe[1]);
	exec(cmd, env);
	close(fd_out);
	return (1);
}

/**
 * The main function of the pipex program.
 * 
 * This function serves as the entry point for the pipex program. It validates the number of command-line arguments
 * and the input/output paths, creates a pipe, and forks the process. In the child process, it calls `write_2_pipe`
 * to write input from a file to the pipe for processing by a command. In the parent process, it calls `read_pipe`
 * to read the processed output from the pipe and write it to an output file. The function ensures proper error
 * handling and resource management throughout its execution.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * @param env The environment variables array.
 * @return Returns 0 upon successful execution, or calls `error_mgmt` in case of an error.
 */
int	main(int argc, char *argv[], char **env)
{
	int		fd_pipe[2];
	int		id;

	if (argc != 5 || argv[2][0] == '\0' || argv[3][0] == '\0')
		error_mgmt(ARGC_ERR, 0);
	if (ft_strrchr(argv[1], '/') - argv[1] == ft_strlen(argv[1]) - 1)
		error_mgmt(INPUT_ERR, argv[1]);
	if (pipe(fd_pipe) == -1)
		error_mgmt(PIPE_ERR, 0);
	id = fork();
	if (id == -1)
		error_mgmt(FORK_ERR, 0);
	if (id == 0)
		write_2_pipe(argv[2], argv[1], fd_pipe, env);
	else if (id != 0)
		read_pipe(argv[3], argv[4], fd_pipe, env);
	return (0);
}
