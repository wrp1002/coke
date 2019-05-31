#pragma once
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>


using namespace std;

class Label
{
public:
	string text;
	int x, y;
	bool active;
	Label(string _text, int _x, int _y, bool _active);
	
	void Draw(ALLEGRO_FONT *font);
};

