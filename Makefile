CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft_malloc_$HOSTTYPE.so
HEADERS = includes/
SRCS = srcs

$(NAME): all
 
all: 
	@$(CC) -c $(CFLAGS) -I $(HEADERS) $(SRCS)/*.c 
	@ar -rc $(NAME) *.o
	@echo "\033[32m$(NAME) built!\033[0m"

	
clean:
	@rm *.o

fclean:
	@rm $(NAME) a.out *.o

re: fclean all

.PHONY: all clean fclean re