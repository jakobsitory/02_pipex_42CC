/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 09:33:48 by jschott           #+#    #+#             */
/*   Updated: 2023/10/05 15:16:47 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
