#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <cassert>
#include <string>

//#include "functions.h"
#include "GraphicsSystem.h"
#include "Game.h"
#include "EventSystem.h"

using namespace std;

int main()
{
	EventSystem::initInstance();
	EventSystem::getInstance()->init();
	Game::initInstance();
	Game::getInstance()->init();
	Game::getInstance()->doLoop();
	Game::cleanupInstance();
	EventSystem::cleanupInstance();

	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");
	return false;
}

//event system/que in lawson dean

//input system fires interface events
//event system handleEvent for interface events
//event listener for input translator 
