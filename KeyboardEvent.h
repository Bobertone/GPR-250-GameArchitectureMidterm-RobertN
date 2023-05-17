#pragma once

#include <string>
#include <trackable.h>
#include <Event.h>
#include <allegro5/allegro.h>
#include "MouseEvent.h"
#include "KeyCode.h"

using namespace std;

enum KeyboardEventType
{
	KEY_UP = NUM_MOUSE_EVENT_TYPES,
	KEY_DOWN
};

class KeyboardEvent : public Event
{
private:
	KeyCode mKey;

public:

	KeyboardEvent(KeyboardEventType type, KeyCode key) :Event((EventType)type), mKey(key) {}
	virtual ~KeyboardEvent() {}
	KeyCode getKey() { return mKey; }
};