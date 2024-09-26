SRCS		= $(wildcard *.c)
NAME		= libft.a
OBJS		= $(SRCS:.c=.o)
CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror
MLX			= /Users/gsaile/Cursus/MLX42/libmlx42.a -lglfw -lm -L "/Users/$$USER/.brew/opt/glfw/lib/"
INC			= /Users/gsaile/Cursus/MLX42/include

.c.o:
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)

fclean:		clean
	@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
