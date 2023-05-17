#include "InputTranslator.h"
#include "EventSystem.h"
#include "MouseEvent.h"
#include "KeyboardEvent.h"
#include "GameEvent.h"

//listen to events
InputTranslator::InputTranslator()
{
	EventSystem::getInstance()->addListener((EventType)M_DOWN, this);
	EventSystem::getInstance()->addListener((EventType)M_UP, this);
	EventSystem::getInstance()->addListener((EventType)KEY_DOWN, this);
	EventSystem::getInstance()->addListener((EventType)KEY_UP, this);
}

//Handle events by translating them to game events
void InputTranslator::handleEvent(const Event& theEvent)
{
	if(theEvent.getType() == M_DOWN)
	{
		switch(((MouseEvent&)theEvent).getButton())
		{
		case 1:
			EventSystem::getInstance()->fireEvent(GameEvent(PLACE_SMURF, ((MouseEvent&)theEvent).getPosition()));
			break;
		case 2:
			EventSystem::getInstance()->fireEvent(GameEvent(REMOVE_SMURF, ((MouseEvent&)theEvent).getPosition()));
			break;
		default:
			break;
		}
	}
	else if (theEvent.getType() == KEY_DOWN) 
	{
		switch (((KeyboardEvent&)theEvent).getKey())
		{
		case ESCAPE:
			EventSystem::getInstance()->fireEvent(GameEvent(CLOSE_GAME));
			break;
		case ENTER:
			EventSystem::getInstance()->fireEvent(GameEvent(SWAP_ANIMATION));
			break;
		case SPACE:
			EventSystem::getInstance()->fireEvent(GameEvent(TOGGLE_ANIMATION));
			break;
		default:
			break;
		}
	}
	
}
