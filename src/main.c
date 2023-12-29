/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 09:27:10 by jschott           #+#    #+#             */
/*   Updated: 2023/10/05 10:21:11 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
