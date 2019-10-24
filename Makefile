# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twitting <twitting@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 14:23:06 by twitting          #+#    #+#              #
#    Updated: 2019/02/27 15:52:41 by twitting         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
SRC = ./wolf_src/getintmap.c \
	  ./wolf_src/main.c \
	  ./wolf_src/raycaster.c \
	  ./wolf_src/userinput.c \
	  ./wolf_src/texture.c \
	  ./wolf_src/sprites.c
SRC2 = ./libft/libft.a
OBJECTS = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror
FLAGS2 = -I includes -I libft -I /usr/local/include -L /usr/local/lib -lmlx -lpthread -framework OpenGL -framework AppKit
FLAGS_LINUX = -I ./includes/ /usr/X11/lib/libmlx.a  -lXext -lX11 -lm -lpthread

all: $(NAME)

linux:
	make re -C libft/
	sudo gcc $(FLAGS) $(SRC) $(SRC2) $(FLAGS_LINUX) -o $(NAME)

$(NAME): $(OBJECTS)
	make -C libft/
	gcc -g $(FLAGS) $(FLAGS2) $(OBJECTS) $(SRC2) -o $(NAME)

%.o: %.c
	gcc $(FLAGS) -I includes -I libft -c $< -o $@

clean:
	make clean -C libft/
	/bin/rm -f $(OBJECTS)

fclean: clean
	make fclean -C libft/
	/bin/rm -f $(NAME)

re: fclean all

re_linux: fclean linux
