# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/26 12:04:52 by rsibiet           #+#    #+#              #
#    Updated: 2016/03/05 14:59:54 by rsibiet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

FTC = main_wolf3d.c \
	  key_mouse_wolf3d.c \
	  user_interface.c \
	  perm_interface.c \
	  loop_wolf3d.c \
	  levels_wolf3d.c

FTO = $(subst .c,.o,$(FTC))

MLX = -L/usr/local/lib/ -I/usr/local/include -lmlx -framework OpenGL \
	  -framework AppKit

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(FTO)
	@echo ""
	@echo "\033[32m ___________________\033[0m"
	@echo "\033[32m| • $(NAME) created! |\033[0m"
	@echo "\033[32m|___________________|\033[0m"
	@echo "\n"
	@echo "\033[34;1m___________________________ Loading libft ______________________________\033[37m\n"
	@make -C ./libft
	@gcc -o $(NAME) $(FTO) ./libft/libft.a $(MLX)

%.o: %.c
	@gcc -Wall -Wextra -Werror -O3 -I./libft/ -c $<
	@echo "\033[42m            \033[0m\c"

clean:
	@make -C ./libft clean
	@rm -rf $(FTO)
	@echo "\033[33m• $(NAME) object deleted!\033[0m"

fclean: clean
	@make -C ./libft fcleana
	@rm -rf $(NAME)
	@echo "\033[31;1m• \033[31m$(NAME) deleted!\033[0m"

re: fclean all
