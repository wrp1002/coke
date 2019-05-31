#include "Label.h"



Label::Label(string _text, int _x, int _y, bool _active) {
	this->text = _text;
	this->x = _x;
	this->y = _y;
	this->active = _active;
}

void Label::Draw(ALLEGRO_FONT *font) {
	if (active) {
		int width = al_get_text_width(font, this->text.c_str());
		al_draw_filled_rectangle(x - width / 2, y, x + width / 2, y + 30, al_map_rgba_f(0, 0, 0, .5));
		al_draw_text(font, al_map_rgb(255, 255, 255), this->x, this->y, ALLEGRO_ALIGN_CENTER, this->text.c_str());
	}
}

