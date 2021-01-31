CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft_malloc_$HOSTTYPE.so
HEADERS = includes/
SRCS = srcs/malloc.c \
		srcs/free.c \
		srcs/utils/create_blocks.c \
		srcs/utils/find_free_block.c \
		srcs/utils/merge_heaps.c \
		srcs/utils/ret_mem_block.c\

$(NAME): all
 
all: 
	@$(CC) -c $(CFLAGS) -I $(HEADERS) $(SRCS)
	@ar -rc $(NAME) *.o
	@echo "\033[32m$(NAME) built!\033[0m"

test:
	@gcc srcs/test.c -L. $(NAME) -o test

clean:
	@rm *.o 

fclean:
	@rm $(NAME) a.out *.o test

re: fclean all

.PHONY: all clean fclean re