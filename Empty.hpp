#ifndef EMPTY_HPP
# define EMPTY_HPP

# include <ncurses.h>
# include "Drawable.hpp"

class Empty : public Drawable
{
	private:

	public:
		Empty(int y, int x) {
			this->x = x;
			this->y = y;
			this->icon = ' ';
		};
};

#endif