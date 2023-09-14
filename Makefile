CC = cc
CFLAGS = -Wall -Wextra -Werror  -g
NAME = so_long
SOURCES = get_next_line.c get_next_line_utils.c so_long.c so_long_utils.c update.c hook.c moves.c error_1.c error_2.c error_3.c utils_more.c
OBJECTS = $(SOURCES:.c=.o)
LIBS =  -lmlx -framework OpenGL -framework AppKit
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(NAME)
	@echo "\033[1;32mDONE!\033[0m"

OBJTS: $(SOURCES)
	$(CC) $(CFLAGS) -c $^

clean : 
	@echo "\033[36mCleaning so_long....\033[0m"
	@rm -rf $(OBJECTS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all