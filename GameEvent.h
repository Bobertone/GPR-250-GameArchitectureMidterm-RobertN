#pragma once

#include <string>
#include <trackable.h>
#include <Event.h>
#include <Vector2D.h>


using namespace std;

enum GameEventType
{
	CLOSE_GAME = NUM_BASE_EVENT_TYPES,
	UNPAUSE_GAME,
	PLACE_SMURF,
	REMOVE_SMURF,
	SWAP_ANIMATION,
	BLUE_ORB_DESTROYED,
	RED_ORB_DESTROYED,
	NUM_GAME_EVENT_TYPES
};

class GameEvent : public Event
{
private:
	Vector2D mPos;
public:
	GameEvent(GameEventType type, Vector2D pos) : Event((EventType)type), mPos(pos) {}
	GameEvent(GameEventType type) : Event((EventType)type), mPos(Vector2D()) {}
	virtual ~GameEvent() {};
	Vector2D getPosition() { return mPos; }
};