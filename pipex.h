/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:44:25 by jschott           #+#    #+#             */
/*   Updated: 2023/10/05 10:24:04 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include "include/Libft/include/libft.h"
# include "include/Libft/include/get_next_line.h"
# include "include/Libft/include/ft_printf.h"

# define ARGC_ERR	1
# define INPUT_ERR	2
# define OUTPUT_ERR	3
# define CMMND_ERR	127
# define PIPE_ERR	5
# define FORK_ERR	6
# define WRITE_ERR	7
# define READ_ERR	8 

int	error_mgmt(int code, char *str);
int	exec(char *cmd, char **env);

#endif
