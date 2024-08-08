/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 09:33:48 by jschott           #+#    #+#             */
/*   Updated: 2024/08/08 11:08:44 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
/**
 * Manages and displays error messages based on error codes.
 * 
 * The function handles various error codes, including:
 * - ARGC_ERR: Incorrect number of command-line arguments.
 * - INPUT_ERR: Input file does not exist.
 * - OUTPUT_ERR: Error while opening or creating the output file.
 * - CMMND_ERR: Specified command does not exist.
 * - PIPE_ERR: Could not open a pipe.
 * - FORK_ERR: Could not fork a new process.
 * - WRITE_ERR: Could not write to a pipe.
 * - READ_ERR: Could not read from a pipe.
 * 
 * @param code The error code indicating the type of error.
 * @param str An optional string providing additional information about the error.
 */
int	error_mgmt(int code, char *str)
{
	write (2, "ERROR\n", 6);
	if (code == ARGC_ERR)
		write(2, "incorrect number of arguments. Execute as followes:\n\
./pipex file1 cmd1 cmd2 file2", 81);
	if (code == INPUT_ERR)
		write(2, "no such file or directory: ", 27);
	if (code == OUTPUT_ERR)
		write(2, "error while opening or creating output file", 43);
	if (code == CMMND_ERR)
		write(2, "command does not exist: ", 24);
	if (code == PIPE_ERR)
		write(2, "could not open pipe", 18);
	if (code == FORK_ERR)
		write(2, "could not fork", 14);
	if (code == WRITE_ERR)
		write(2, "could not write to pipe ", 24);
	if (code == READ_ERR)
		write(2, "could not read from pipe ", 24);
	if (str)
		write(2, str, ft_strlen(str));
	write (2, "\n", 1);
	exit (code);
}
