#pragma once

#include <string>
#include <trackable.h>
#include <Event.h>
#include <allegro5/allegro.h>
#include "GameEvent.h"
#include "Vector2D.h"

using namespace std;

enum MouseEventType
{
	M_DOWN = NUM_GAME_EVENT_TYPES,
	M_UP,
	NUM_MOUSE_EVENT_TYPES
};

class MouseEvent :public Event
{
private:
	int mMouseButton;
	Vector2D mMousePos;

public:

	MouseEvent(MouseEventType type, int mButton, Vector2D mPos) :Event((EventType)type), mMouseButton(mButton), mMousePos(mPos) {}
	virtual ~MouseEvent() {};
	int getButton() { return mMouseButton; }
	Vector2D getPosition() { return mMousePos; }
};