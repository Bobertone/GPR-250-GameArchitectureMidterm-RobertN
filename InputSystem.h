#pragma once
#include <allegro5/allegro.h>
#include <Trackable.h>
#include <Vector2D.h>
#include "KeyCode.h"
//InputSystem - The class which has functions to get keyboard / mouse state.Should not contain any game specific code

/*
• Left mouse down will place Unit at mouse location (centered)
• “F” key will speed up animation by a visible amount
• “S” key will slow down animation by a visible amount
• “Enter” key will switch between the 2 animations
• “Escape” key will close application
*/

class InputSystem : public Trackable
{
private:
	////-DATA-
	// Any data necessary to fulfill the requirements of the assignment
	ALLEGRO_EVENT_QUEUE* mpEventQueue = nullptr;
public:
	////-FUNCTIONS-
	
	// Constructor / Destructor
	InputSystem() {};
	~InputSystem() { cleanup(); }

	// Init / Cleanup
	bool init();
	void cleanup();

	// getKeyState, getMouseState
	bool getKeyState(KeyCode key);
	bool getMouseState(int button);
	Vector2D getMousePos();

	void update(float dt);
	

};

