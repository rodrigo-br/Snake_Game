#ifndef BOARD_HPP
# define BOARD_HPP

# include <ncurses.h>
# include <time.h>
# include <stdlib.h>
# include "Drawable.hpp"
# include "Time.hpp"

class Board
{
	private:
		WINDOW	*win;
		int		height, width;
		int		start_x, start_y;
		int		timeout;

	public:
		Board();
		Board(int height, int width);
		~Board();

		void	add_border();
		void	clear();
		void	refresh();
		void	initialize();
		void	add(Drawable drawable);
		void	add_at(int y, int x, chtype c);
		void	get_empty_coordinates(int &y, int &x);
		chtype	get_input();
		void	set_timeout(int timeout);
		void	pause(int timeout);
		chtype	get_char_at(int y, int x);
		int		get_width() const;
		int		get_height() const;
		int		get_start_x() const;
		int		get_start_y() const;
		int		get_timeout() const;
		void	increase_speed();
};

Board::Board() {}

Board::Board(int height, int width) : height(height), width(width) {
	int xMax, yMax;
	this->timeout = 300;

	getmaxyx(stdscr, yMax, xMax);
	this->start_x = (xMax / 2) - (width / 2);
	this->start_y = (yMax / 2) - (height / 2);
	this->win = newwin(height, width, start_y, start_x);
	wtimeout(this->win, timeout);
	keypad(this->win, true);
	initialize();
}

Board::~Board() {}

void Board::add_border() {
	box(this->win, 0, 0);
}

void Board::clear() {
	wclear(this->win);
	add_border();
}

void Board::get_empty_coordinates(int &y, int &x) {
	while ((mvwinch(this->win, y = rand() % this->height, x = rand() % this->width)) != ' ')
		;
}

void Board::add(Drawable drawable) {
	add_at(drawable.get_y(), drawable.get_x(), drawable.get_icon());
}

void Board::add_at(int y, int x, chtype c) {
	mvwaddch(this->win, y, x, c);
}

chtype Board::get_input() {
	time_t time_last_input = Time::milliseconds();

	chtype input = wgetch(this->win);
	chtype new_input = ERR;

	set_timeout(0);
	while (time_last_input + this->timeout >= Time::milliseconds()) {
		new_input = wgetch(this->win);
	}
	set_timeout(this->timeout);

	if (new_input != ERR)
		input = new_input;

	return input;
}

void Board::refresh() {
	wrefresh(this->win);
}

void Board::initialize() {
	clear();
	refresh();
}

void Board::set_timeout(int timeout) {
	wtimeout(this->win, timeout);
}

void Board::pause(int timeout) {
	this->set_timeout(-1);
	while (this->get_input() != 'p')
		;
	this->set_timeout(timeout);
}

chtype Board::get_char_at(int y, int x) {
	return mvwinch(this->win, y, x);
}

int Board::get_width() const {
	return this->width;
}

int Board::get_height() const {
	return this->height;
}

int Board::get_start_x() const {
	return this->start_x;
}

int Board::get_start_y() const {
	return this->start_y;
}

int Board::get_timeout() const {
	return this->timeout;
}

void Board::increase_speed() {
	this->timeout /= 1.3;
	this->set_timeout(this->timeout);
}

#endif