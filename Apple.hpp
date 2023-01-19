#ifndef APPLE_HPP
# define APPLE_HPP

# include <ncurses.h>
# include "Drawable.hpp"

class Apple : public Drawable
{
	private:
		
	public:
		Apple(int y, int x) {
			this->x = x;
			this->y = y;
			this->icon = '@';
		};
};

#endif