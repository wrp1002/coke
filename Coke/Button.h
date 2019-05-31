#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#include <string>
#include <iostream>

using namespace std;

class Button {
private:
	int x, y, width, height, clickOffset, id;
	bool hovering;
	bool clicked;
	string text;
	ALLEGRO_COLOR color;
	ALLEGRO_COLOR hoverColor;

public:
	Button(int x, int y, int width, int height, int id, string text, ALLEGRO_COLOR color, ALLEGRO_COLOR hoverColor);

	int GetID();
	bool CheckMouse(int mouseX, int mouseY);
	bool GetClicked();

	void SetHover(bool _hovering);
	void SetClicked(bool _clicked);

	void Draw(ALLEGRO_FONT *font);
};

