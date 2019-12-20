# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/03 15:08:28 by kbessa            #+#    #+#              #
#    Updated: 2019/12/13 16:57:13 by kbessa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= lem_in

CFLAGS 	= -Wall -Wextra -Werror

SRC 	= lem_main.c help.c rooms.c ants.c bfs.c

RED		=	\033[0;31m
GREEN	=	\033[0;32m
GREENBG	=	\033[1;42;30m
YELLOW	=	\x1B[93m
ORANGE	=	\x1B[38;5;208m
NC		=	\033[0m
COOL2	=	\033[01;38;05;97m
FON		=	\033[01;48;05;22m
LAGUNA	=	\033[01;38;05;51m

OBJSFD 	= objects

OBJS 	= $(addprefix $(OBJSFD)/,$(SRC:.c=.o))

HDR 		= -I./includes
LIBFT_HDR 	= -I./libft/includes
LIB_BINARY	= -L./libft -lft
LIBFT		= libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft

$(OBJSFD):
	@mkdir $@

$(OBJSFD)/%.o: %.c | $(OBJSFD)
	@$(CC) $(CFLAGS) $(HDR) $(LIBFT_HDR) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀$(NC)							       $(COOL2)❒$(NC)"
	@echo "$(YELLOW)▀ Compiling $@... ▀$(NC)							       $(COOL2)❒$(NC)"
	@echo "$(YELLOW)▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀$(NC)							       $(COOL2)❒$(NC)"
	@gcc $(CFLAGS) $(OBJS) $(LIB_BINARY) -o $@
	@echo "✅  $(GREEN)$@ Ready!$(NC) ✅							       $(COOL2)❒$(NC)"
	@echo "									       $(COOL2)❒"
	@echo	"			    	$(RED)  ▄  ▄    ▄▀$(NC)				       $(COOL2)❒$(NC)"
	@echo	"			    	$(RED)   ▀▄ █ ▄▀▄▄▄$(NC)				       $(COOL2)❒$(NC)"
	@echo	"			    	$(RED)▄██▄████▄██▄▀█▄$(NC)			               $(COOL2)❒$(NC)"
	@echo	"			    	$(RED) ▀▀─█▀█▀▄▀███▀$(NC)			               $(COOL2)❒$(NC)"
	@echo	"			    	$(RED)  ▄▄▀ █  ▀▄▄$(NC)			               $(COOL2)❒$(NC)"
	@echo	"$(COOL2)❐▄❒▄❒▄❒▄❐▄❒▄❒▄❒▄❐▄❒▄❒▄❒▄❐▄❒▄❐▄❒▄❒▄❒▄❐▄❒▄❒▄❒▄❐▄❒▄❒▄❒▄❐▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄$(NC)	"

clean:
	@echo "$(RED)deleting lem-in object files...$(NC) ✔"
	@echo "$(RED)----------------------------------$(NC)"
	@/bin/rm -f $(OBJS)
	@rm -rf $(OBJSFD)
	@make -C ./libft fclean

fclean: clean
	@echo "$(RED)deleting lem-in executable files...$(NC) ✔"
	@/bin/rm -f $(NAME)

re: fclean all
