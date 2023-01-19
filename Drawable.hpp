#ifndef DRAWABLE_HPP
# define DRAWABLE_HPP

class Drawable
{
	protected:
		int x, y;
		chtype icon;
		
	public:
		Drawable();
		Drawable(int y, int x, chtype icon);
		~Drawable();

		int get_x() const;
		int get_y() const;
		chtype get_icon() const;
};

Drawable::Drawable() : x(0), y(0), icon(' ') {
}

Drawable::Drawable(int y, int x, chtype icon) : x(x), y(y), icon(icon) {
}

Drawable::~Drawable() {
}

int Drawable::get_x() const {
	return this->x;
}

int Drawable::get_y() const {
	return this->y;
}

chtype Drawable::get_icon() const {
	return this->icon;
}


#endif