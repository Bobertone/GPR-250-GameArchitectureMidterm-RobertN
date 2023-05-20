#pragma once
#include <allegro5/allegro.h>
/*
• Welcome screen (hit space to start)
• Pause screen (hit space to unpause, esc to exit) – entered by hitting esc
• When the user left clicks on an orb it changes animation
*/
enum KeyCode
{
	ESCAPE = ALLEGRO_KEY_ESCAPE,
	ENTER = ALLEGRO_KEY_ENTER,
	SPACE = ALLEGRO_KEY_SPACE,
};