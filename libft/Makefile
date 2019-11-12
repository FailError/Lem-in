# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 15:35:58 by kbessa            #+#    #+#              #
#    Updated: 2019/11/02 16:12:28 by kbessa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

FT_PRINTF = ft_char.c ft_checkprocent.c ft_checkstruct.c ft_decimal.c	\
ft_decimal2.c ft_decimal3.c ft_float.c ft_float2.c ft_float3.c	\
ft_floatprecnull1.c ft_floatprecnull2.c ft_help.c ft_odecimal.c	\
ft_odecimalmin.c ft_pointer.c ft_printf.c ft_printf2.c ft_string.c	\
ft_string2.c ft_udecimal.c ft_udecimalmin.c ft_xhex.c ft_xhexmin.c	\
ft_xhexx.c ft_xhexxmin.c

LIBFT =	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c	\
ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c 	\
ft_lstiter.c ft_slen.c ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c	\
ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c	\
ft_putchar.c ft_putchar_fd.c ft_word_count.c ft_putendl.c ft_putendl_fd.c	\
ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c	\
ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c	\
ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c	\
ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c	\
ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c	\
ft_tolower.c ft_toupper.c ft_swap.c ft_strndup.c get_next_line.c

.PHONY: all clean fclean re

RED			=	\033[0;31m
YELLOW		=	\x1B[93m
GREEN		=	\033[0;32m
NC			=	\033[0m
NC1			=	\033[5m
COOL		=	\033[38;5;206;48;5;57m

OBJSFD = objects

FT_PRINTF_SRCS = $(addprefix srcs/ft_printf/,$(FT_PRINTF))

LIBFT_SRCS = $(addprefix srcs/,$(LIBFT))

SRCS = $(LIBFT_SRCS) $(FT_PRINTF_SRCS)

OBJECTS = $(LIBFT:.c=.o) $(FT_PRINTF:.c=.o)

OBJS = $(addprefix $(OBJSFD)/, $(OBJECTS))

VPATH =	srcs:srcs/ft_printf

all: $(NAME)

$(NAME): $(OBJS)

	@echo	"❐▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄❒▄"
	@echo	"									       ❐"
	@echo  "			$(COOL)████─█─█─███─█──█─███─█───█─████─████$(NC)		       ❐"
	@echo  "			$(COOL)█──█─█─█─█───█──█─█───█───█─█──█─█──█$(NC)		       ❐"
	@echo  "			$(COOL)████─█─█─███─████─███─█─█─█─████─████$(NC)		       ❒"
	@echo  "			$(COOL)█────█─█───█─█──█───█─█████─█──█─█$(NC)		       ❒"
	@echo  "			$(COOL)█────███─███─█──█─███──█─█──█──█─█$(NC)		       ❒"
	@echo	"									       ❒"
	@echo  "				  $(COOL)████──██─██$(NC)				       ❒"
	@echo  "				  $(COOL)█──██──███$(NC)				       ❒"
	@echo  "				  $(COOL)████────█$(NC)				       ❒"
	@echo  "				  $(COOL)█──██───█$(NC)				       ❒"
	@echo  "				  $(COOL)████────█$(NC)				       ❒"
	@echo  "				  $(COOL)────────█$(NC)				       ❒"
	@echo	"									       ❒"
	@echo	"			  $(COOL)█──█─████──███─███─███─████$(NC)			       ❒"
	@echo	"			  $(COOL)█─█──█──██─█───█───█───█──█$(NC)			       ❒"
	@echo	"			  $(COOL)██───████──███─███─███─████$(NC)			       ❒"
	@echo	"			  $(COOL)█─█──█──██─█─────█───█─█──█$(NC)			       ❒"
	@echo	"			  $(COOL)█──█─████──███─███─███─█──█$(NC)			       ❒"
	@echo	"									       ❒"
	@echo "$(YELLOW)▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀$(NC)							       ❒"
	@echo "$(YELLOW)▀ Making archive... ▀$(NC)							       ❒"
	@echo "$(YELLOW)▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀ ▀$(NC)							       ❒"
	@ar rc $@ $(OBJS)
	@ranlib $@
	@echo "✅  $(GREEN)libft.a Created!$(NC) ✅							       ❒"
	@echo "									       ❒"

$(OBJSFD):
	@mkdir $@

$(OBJSFD)/%.o: %.c | $(OBJSFD)
	@$(CC) $(CFLAGS) $(HDR) -c $< -o $@

HDR = -I./includes

clean:
	@echo "$(RED)deleting libft object files...$(NC) ✔"
	@echo "$(RED)------------------------------$(NC)"
	@/bin/rm -f $(OBJS)
	@rm -rf $(OBJSFD)

fclean: clean
	@echo "$(RED)deleting libft.a archive...$(NC) ✔"
	@echo "$(RED)---------------------------$(NC)"
	@/bin/rm -f $(NAME)

re: fclean all
