NAME = GameOfLife

SRCS = main.c

OBJS = main.o

INCLUDE = ./include/common.h

FLAG = -Weverything -fsanitize=address

CC = clang

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAG) -o $(NAME) $(OBJS)

%o : %c $(INCLUDE)
	$(CC) -c $(FLAG) $< -o $@ $(INCLUDE)

clean :
	/bin/rm -fr $(OBJS)

fclean : clean
	/bin/rm -fr $(NAME)

re : fclean all
