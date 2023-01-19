#ifndef SNAKEGAME_HPP
# define SNAKEGAME_HPP

# include "Board.hpp"
# include "Drawable.hpp"
# include "Apple.hpp"
# include "Empty.hpp"
# include "Snake.hpp"
# include "ScoreBoard.hpp"
# include <SDL2/SDL.h>

class SnakeGame
{
	private:
		Board		board;
		bool		game_over;
		Apple		*apple;
		Snake 		snake;
		ScoreBoard	score_board;
		int			score;
		
	public:
		SnakeGame(int height, int width);
		~SnakeGame();

		void initialize();
		void process_input();
		void update_state();
		void redraw();
		bool is_game_over();
};

SnakeGame::SnakeGame(int height, int width) {
	this->board = Board(height, width);
	int sb_x, sb_y;
	sb_y = board.get_start_y() + height;
	sb_x = board.get_start_x();
	this->score_board = ScoreBoard(width, sb_y, sb_x);
	initialize();
}

SnakeGame::~SnakeGame() {
	delete apple;
}

void SnakeGame::initialize() {
	this->score = 0;
	score_board.initialize(this->score);
	this->game_over = false;
	this->apple = NULL;
	srand(time(NULL));

	SnakePiece next = SnakePiece(1, 1);
	board.add(next);
	snake.add_piece(next);

	next = snake.next_head();
	board.add(next);
	snake.add_piece(next);

	next = snake.next_head();
	board.add(next);
	snake.add_piece(next);
}

void SnakeGame::process_input() {
	chtype input = board.get_input();

	int old_timeout = board.get_timeout();
	switch(input)
	{
		case KEY_UP:
		case 'w':
			snake.set_direction(UP);
			break;
		case KEY_DOWN:
		case 's':
			snake.set_direction(DOWN);
			break;
		case KEY_LEFT:
		case 'a':
			snake.set_direction(LEFT);
			break;
		case KEY_RIGHT:
		case 'd':
			snake.set_direction(RIGHT);
			break;
		case 'p':
			board.pause(old_timeout);
			break;
		default:
			break;
	}
}

void SnakeGame::update_state() {
	if (!apple)
	{
		int x, y;
		board.get_empty_coordinates(y, x);
		apple = new Apple(y, x);
		board.add(*apple);
	}

	SnakePiece next = snake.next_head();
	if (board.get_char_at(next.get_y(), next.get_x()) == '#' ||
		next.get_x() < 1 || next.get_x() >= board.get_width() ||
		next.get_y() < 1 || next.get_y() >= board.get_height() - 1)
	{
		this->game_over = true;
	}
	else if ((next.get_y() != apple->get_y() || next.get_x() != apple->get_x()))
	{
		int empty_y = snake.tail().get_y();
		int empty_x = snake.tail().get_x();
		board.add(Empty(empty_y, empty_x));
		snake.remove_piece();
	}
	else {
		delete apple;
		apple = NULL;
		this->score++;
		score_board.update_score(this->score);
		if (this->score % 5 == 0) {
			board.increase_speed();
		}
	}
	board.add(next);
	snake.add_piece(next);
}

void SnakeGame::redraw() {
	board.refresh();
	score_board.refresh();
}

bool SnakeGame::is_game_over() {
	return this->game_over;
}

#endif
