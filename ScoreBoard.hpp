#ifndef SCOREBOARD_HPP
# define SCOREBOARD_HPP

class ScoreBoard
{
	private:
		WINDOW *score_win;

	public:
		ScoreBoard();
		ScoreBoard(int width, int y, int x);
		~ScoreBoard();

		void clear();
		void refresh();
		void initialize(int initial_score);
		void update_score(int score);
};

ScoreBoard::ScoreBoard() {
}

ScoreBoard::ScoreBoard(int width, int y, int x) {
	this->score_win = newwin(1, width, y, x);
}

ScoreBoard::~ScoreBoard() {
}

void ScoreBoard::initialize(int initial_score) {
	clear();
	mvwprintw(this->score_win, 0, 0, "Score:");
	update_score(initial_score);
	refresh();
}

void ScoreBoard::update_score(int score) {
	mvwprintw(this->score_win, 0, score_win->_maxx - 10, "%11llu", score);
}

void ScoreBoard::clear() {
	wclear(this->score_win);
}

void ScoreBoard::refresh() {
	wrefresh(this->score_win);
}

#endif