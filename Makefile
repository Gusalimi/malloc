# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 10:38:20 by gsaile            #+#    #+#              #
#    Updated: 2024/10/12 11:54:30 by gsaile           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =============== VARIABLES ===============

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		:= libft_malloc_$(HOSTTYPE).so

LIBFT_DIR	:= libft
LIBFT_AR	:= $(LIBFT_DIR)/libft.a

CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra -g3 -fPIC
RM			:= rm -rf

SRCDIR		:= src
OBJDIR		:= .objFiles

FILES		:= malloc free realloc show_alloc_mem

SRCS		:= $(addprefix $(SRCDIR)/, $(FILES:=.c))
OBJS		:= $(addprefix $(OBJDIR)/, $(FILES:=.o))

#Colors:
GREEN		:=	\e[92;5;118m
YELLOW		:=	\e[93;5;226m
GRAY		:=	\e[33;2;37m
RESET		:=	\e[0m
BOLD        :=   \e[1m

# =============== RULES ===============

all: $(NAME)

$(NAME): $(LIBFT_AR) $(OBJS)
	@printf "[Building] $(BOLD)$(NAME)$(RESET): "
	@$(CC) $(CFLAGS) -shared $(OBJS) -lft -L$(LIBFT_DIR) -o $(NAME)
	@printf "$(GREEN)Done$(RESET)\n"
	@ln -sf $(NAME) libft_malloc.so

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@printf "[Building] $(BOLD)$(notdir $@)$(RESET): "
	@$(CC) $(CFLAGS) $(OPTS) -c $< -o $@
	@printf "$(GREEN)Done$(RESET)\n"

$(LIBFT_AR):
	@printf "[Building] $(BOLD)libft$(RESET): "
	@$(MAKE) -C $(LIBFT_DIR)
	@printf "$(GREEN)Done$(RESET)\n"

clean:
	@printf "[Cleaning] $(BOLD).o files$(RESET): "
	@$(RM) $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@printf "$(GREEN)Done$(RESET)\n"

fclean: clean
	@printf "[Deleting] $(BOLD)$(NAME)$(RESET): "
	@$(RM) $(NAME) libft_malloc.so
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@printf "$(GREEN)Done$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
