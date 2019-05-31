#include "Button.h"



Button::Button(int x, int y, int width, int height, int id, string text, ALLEGRO_COLOR color, ALLEGRO_COLOR hoverColor) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->text = text;
	this->id = id;
	this->color = color;
	this->hoverColor = hoverColor;

	this->id = id;
	this->clickOffset = 3;
	this->hovering = false;
	this->clicked = false;
}

int Button::GetID() {
	return id;
}

bool Button::CheckMouse(int mouseX, int mouseY) {
	return (mouseX > x && mouseX < x + width && mouseY > y && mouseY < y + height);
}

bool Button::GetClicked()
{
	return clicked;
}

void Button::SetClicked(bool _clicked) {
	this->clicked = _clicked;
}

void Button::SetHover(bool _hovering) {
	this->hovering = _hovering;
}

void Button::Draw(ALLEGRO_FONT *font) {
	al_draw_filled_rectangle(x + clickOffset, y + clickOffset, x + width + clickOffset, y + height + clickOffset, al_map_rgb(0, 0, 0));
	al_draw_filled_rectangle(x + clickOffset * clicked, y + clickOffset * clicked, x + width + clickOffset * clicked, y + height + clickOffset * clicked, (this->hovering ? this->hoverColor : this->color));
	al_draw_text(font, al_map_rgb(0, 0, 0), x + width / 2 + clickOffset * clicked, y + 3 + clickOffset * clicked, ALLEGRO_ALIGN_CENTER, text.c_str());
}