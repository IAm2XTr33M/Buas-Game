#include "EventSystem.h"

#include "Events/EventSub.h"
#include "Events/GameEvent.h"

EventSystem::EventSystem() {

}

void EventSystem::RunEvent(char* _name, GameObject* _gameObject) {
	GameEvent* _event = &GameEvent(_name, _gameObject);
	for each (EventSub* subbedEvent in subbedEvents)
	{
		if (subbedEvent->name == _event->eventName) {
			
			subbedEvent->func(_event);
		}
	}
}

void EventSystem::RunEvent(char* _name, GameObject* _gameObject, char* _context) {
	GameEvent* _event = &GameEvent(_name, _gameObject);

	for each (EventSub * subbedEvent in subbedEventsContext)
	{
		if (subbedEvent->name == _event->eventName &&
			subbedEvent->context == _event->context) {

			subbedEvent->func(_event);
		}
	}
}

void EventSystem::ListenForEvent(char* _name, std::function<void(GameEvent*)> _func) {
	subbedEvents.push_back(new EventSub(_name, _func));
}

void EventSystem::ListenForEventContext(char* _name, std::function<void(GameEvent*)> _func, char* _context) {
	subbedEventsContext.push_back(new EventSub(_name, _func, _context));
}