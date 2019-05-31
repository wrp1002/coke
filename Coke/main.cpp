#define _USE_MATH_DEFINES

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_memfile.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "resources.h"
#include "Button.h"
#include "Label.h"
#include "CokePoint.h"

const int WSCREEN = 300;
const int HSCREEN = 250;

using namespace std;

enum STATE {ASK, NO, YES};

int main() {
	srand(time(0));

	int state = ASK;
	int waitTimerStart = 200;
	int waitTimer = waitTimerStart;

	bool done = false, redraw = true;
	int colorTimer = 0;
	vector<Button> buttons;
	vector<CokePoint> cokePoints;

	//!hovering * 50, 205 + hovering * 50, !hovering * 50

	Label label = Label("Are you thirsy for cola?", WSCREEN / 2, 35, true);
	buttons.push_back(Button(WSCREEN / 2 - 50 - 30, 100, 60, 40, 0, "no", al_map_rgb_f(1, 0, 0), al_map_rgb_f(.8, .2, .2)));
	buttons.push_back(Button(WSCREEN / 2 + 50 - 30, 100, 60, 40, 1, "YES!", al_map_rgb_f(0, 1, 0), al_map_rgb_f(.2, .8, .2)));

	ShowWindow(GetConsoleWindow(), SW_HIDE);

	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();

	ALLEGRO_DISPLAY *display = al_create_display(WSCREEN, HSCREEN);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
	ALLEGRO_FILE *file;
	ALLEGRO_BITMAP *cokeImage;
	ALLEGRO_FONT *arial;

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	file = al_open_memfile(cokeHEX, sizeof(cokeHEX), "r");
	cokeImage = al_load_bitmap_f(file, ".png");
	
	file = al_open_memfile(arialHEX, sizeof(arialHEX), "r");
	arial = al_load_ttf_font_f(file, "arial.ttf", 26, NULL);

	if (!arial || !cokeImage) {
		printf("Error loading memfiles");
		system("pause");
		exit(EXIT_FAILURE);
	}

	al_start_timer(timer);

	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		switch (ev.type) {

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
			{
				done = true;
				break;
			}

			case ALLEGRO_EVENT_TIMER:
			{
				redraw = true;
				colorTimer++;

				if ((state == ASK || state == YES) && (rand() % (state == YES ? 50 : 100) == 0)) 
					cokePoints.push_back(CokePoint(rand() % WSCREEN, rand() % HSCREEN, WSCREEN, HSCREEN));
				else if (state == NO) {
					waitTimer--;
					if (waitTimer <= 0) {
						waitTimer = waitTimerStart;
						state = ASK;
						label.text = "How about now?";
					}
				}

				for (auto &point : cokePoints)
					point.Update(WSCREEN, HSCREEN);

				for (unsigned i = 0; i < cokePoints.size();) {
					if (cokePoints[i].lifeState == 2)
						cokePoints.erase(cokePoints.begin() + i);
					else
						i++;
				}

				break;
			}
			case ALLEGRO_EVENT_MOUSE_AXES:
			{
				for (auto &button : buttons) {
					if (button.CheckMouse(ev.mouse.x, ev.mouse.y)) button.SetHover(true);
					else button.SetHover(false);
				}
				break;
			}
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			{
				for (auto &button : buttons) {
					if (button.CheckMouse(ev.mouse.x, ev.mouse.y)) button.SetClicked(true);
					else button.SetClicked(false);
				}
				break;
			}
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			{
				for (auto &button : buttons) {
					if (button.GetClicked()) {
						if (button.GetID() == 0) {
							label.text = "oh";
							state = NO;
							for (auto &point : cokePoints)
								point.speed *= 10;
						}
						else if (button.GetID() == 1) {
							label.text = "Here is a cup holder!";
							state = YES;

							mciSendString("open cdaudio", 0, 0, 0);
							mciSendString("set CDAudio door open", 0, 0, 0);
						}
					}
					button.SetClicked(false);
				}
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			if (state == ASK)
				al_clear_to_color(al_map_rgb(255, abs(sin(colorTimer / 100.0)) * 150, 0));
			else if (state == NO)
				al_clear_to_color(al_map_rgb(0, 0, 0));
			
			for (auto &point : cokePoints)
				al_draw_scaled_rotated_bitmap(cokeImage, al_get_bitmap_width(cokeImage) / 2, al_get_bitmap_height(cokeImage) / 2, point.x, point.y, point.sizeMult, point.sizeMult, point.angle, NULL);

			if (state == ASK) {
				for (auto &button : buttons)
					button.Draw(arial);
			}

			label.Draw(arial);

			al_flip_display();
		}

	}
}