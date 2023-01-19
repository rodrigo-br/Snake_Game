#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <ncurses.h>
# include "Drawable.hpp"
# include <queue>

enum Direction {
	UP = -1,
	DOWN = 1,
	LEFT = -2,
	RIGHT = 2
};

class SnakePiece : public Drawable
{
	private:
		
	public:
		SnakePiece() {
			this->x = this->y = 0;
			this->icon = '#';
		};
		SnakePiece(int y, int x) {
			this->x = x;
			this->y = y;
			this->icon = '#';
		};
};


class Snake
{
	private:
		std::queue<SnakePiece> snake;
		Direction direction;

	public:
		Snake();
		~Snake();

		void 		add_piece(SnakePiece piece);
		void 		remove_piece();
		SnakePiece 	tail() const;
		SnakePiece 	head() const;
		Direction 	get_direction() const;
		void 		set_direction(Direction d);
		SnakePiece 	next_head();
};

Snake::Snake() {
	this->direction = RIGHT;
}

Snake::~Snake() {
}

void Snake::add_piece(SnakePiece piece) {
	this->snake.push(piece);
}

void Snake::remove_piece() {
	this->snake.pop();
}

SnakePiece Snake::tail() const {
	return this->snake.front();
}

SnakePiece Snake::head() const {
	return this->snake.back();
}

Direction Snake::get_direction() const {
	return this->direction;
}

void Snake::set_direction(Direction d) {
	if (this->direction + d != 0)
		this->direction = d;
}

SnakePiece Snake::next_head() {
	int nextY = this->head().get_y();
	int nextX = this->head().get_x();

	switch(this->direction) {
		case UP:
			nextY--;
			break;
		case DOWN:
			nextY++;
			break;
		case LEFT:
			nextX--;
			break;
		case RIGHT:
			nextX++;
			break;
	}

	return SnakePiece(nextY, nextX);
}


#endif