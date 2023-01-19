NAME = snake

all: clear $(NAME)

clear:
		rm -f $(NAME)
		rm -f leaks

$(NAME): main.cpp Board.hpp SnakeGame.hpp Empty.hpp Apple.hpp
		c++ -g3 main.cpp -lSDL2main -lSDL2 -lncurses -o $(NAME)

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="leaks" ./$(NAME)
