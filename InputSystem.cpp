#include "InputSystem.h"
#include "EventSystem.h"
#include "MouseEvent.h"
#include "KeyboardEvent.h"

bool InputSystem::init()
{
	al_install_keyboard();
	al_install_mouse();
	mpEventQueue = al_create_event_queue();
	al_register_event_source(mpEventQueue, al_get_keyboard_event_source());
	al_register_event_source(mpEventQueue, al_get_mouse_event_source());
	return true;
}

void InputSystem::cleanup()
{
	al_destroy_event_queue(mpEventQueue);
	al_uninstall_keyboard();
	al_uninstall_mouse();
}

bool InputSystem::getKeyState(KeyCode key)
{
	ALLEGRO_KEYBOARD_STATE theState;
	al_get_keyboard_state(&theState);
	return (al_key_down(&theState, key));
}

bool InputSystem::getMouseState(int button)
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);
	return al_mouse_button_down(&mouseState, button);
}

Vector2D InputSystem::getMousePos()
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);
	Vector2D mousePos((float)mouseState.x, (float)mouseState.y);
	return mousePos;
}

void InputSystem::update(float dt)
{
	ALLEGRO_EVENT alEvent;
	while(al_get_next_event(mpEventQueue, &alEvent))
	{
		switch (alEvent.type)
		{
		case ALLEGRO_EVENT_KEY_DOWN:
			EventSystem::getInstance()->fireEvent(KeyboardEvent(KEY_DOWN, (KeyCode)alEvent.keyboard.keycode));
			break;
		case ALLEGRO_EVENT_KEY_UP:
			EventSystem::getInstance()->fireEvent(KeyboardEvent(KEY_UP, (KeyCode)alEvent.keyboard.keycode));
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			EventSystem::getInstance()->fireEvent(MouseEvent(M_DOWN, alEvent.mouse.button, Vector2D(alEvent.mouse.x, alEvent.mouse.y)));
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			EventSystem::getInstance()->fireEvent(MouseEvent(M_UP, alEvent.mouse.button, Vector2D(alEvent.mouse.x, alEvent.mouse.y)));
			break;
		
		default:
			break;
		}
	
	}
}
