# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 15:00:12 by jschott           #+#    #+#              #
#    Updated: 2023/10/09 10:31:45 by jschott          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

# SOURCES
SRCDIR = src
SRC = 	main.c \
		error_mgmt.c \
		exec.c

# INCLUDES
HDRS = pipex.h

# LIBRARIES
LIBFTNAME = libft.a
LIBFTDIR = ./include/Libft

# COMPILATION CMNDS
CC = cc
FT_FLAGS = -g -Wextra -Werror -Wall
INCLUDES = -I$(LIBFTDIR)
LDFLAGS = -L$(LIBFTDIR) -lft

# COMPILATION FILES
SRCS = $(addprefix $(SRCDIR)/,$(SRC))
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

all: $(NAME)
	@echo "\n\nCompilation finished successfully\nHave fun breaking things\n"

$(NAME): $(OBJS)
	@echo "\n\nCompiling Executable\n"
	$(CC) $(FT_FLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	@echo "\nExecutable compiled\n\n"

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(HDRS) | makelibft
	@echo "\n\nCompiling Object Files\n"
	$(CC) $(FT_FLAGS) $(INCLUDES) -c $< -o $@
	@echo "\nObject files compiled successfully\n\n"

makelibft:
	@echo "\n\nCompiling LibfFt\n"
	@make -C $(LIBFTDIR)
	@cp $(LIBFTDIR)/$(LIBFTNAME) .
	@echo "\n\nLibft is compiled & ready\n"

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFTNAME)

re: fclean all

.PHONY: all clean fclean re
