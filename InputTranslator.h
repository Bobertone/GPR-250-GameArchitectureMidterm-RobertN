#pragma once
#include "EventListener.h"

class InputTranslator : public EventListener
{
public:
	//listen to events
	InputTranslator();
	~InputTranslator() {};////EventSystem::getInstance()->removeListenerFromAllEvents(EventListener * pListener);
	
	//Handle events by translating them to game events
	virtual void handleEvent(const Event& theEvent) override;
};

