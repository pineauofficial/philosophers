# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pineau <pineau@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 14:55:40 by pineau            #+#    #+#              #
#    Updated: 2023/07/04 17:02:00 by pineau           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philosophers

CC	= gcc

CFLAGS	= -Werror -Wextra -Wall -g3

INC	= -I ./include/

SRC_PATH	= ./srcs/

SRC	= \
		main.c\
		utils.c\
		check_args.c\
		list_maker.c\
		action.c\
		threads.c\
		init.c\
		mutex.c\
		
		
	
SRCS        = $(addprefix $(SRC_PATH), $(SRC))
OBJ_PATH    = obj/
OBJ        = $(SRC:.c=.o)
OBJS        = $(addprefix $(OBJ_PATH), $(OBJ))

$(NAME): $(OBJ_PATH) $(OBJS)
	@echo "Compiling philosophers..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INC)
	@echo "philosophers ready."

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)
	
clean:
	@echo "Removing .o object files..."
	@rm -rf $(OBJ_PATH)


fclean: clean
	@echo "Removing philosophers..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean