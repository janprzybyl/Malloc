CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft_malloc_$HOSTTYPE.so
HEADERS = inc/
SRC = src/malloc.c \
		src/free.c \
		src/utils/setup_heap.c \
		src/utils/find_free_block.c \
		src/utils/merge_heaps.c \
		src/utils/ret_mem_block.c\

$(NAME): all
 
all: 
	@$(CC) -c $(CFLAGS) -I $(HEADERS) $(SRC)
	@ar -rc $(NAME) *.o
	@echo "\033[32m$(NAME) built!\033[0m"

test:
	@gcc src/test.c -L. $(NAME) -o test

clean:
	@rm *.o 

fclean:
	@rm $(NAME) a.out *.o test

re: fclean all

.PHONY: all clean fclean re