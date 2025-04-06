#pragma once
#include "functional"

class GameEvent;
class EventSub;
class GameObject;

class EventSystem {
public:
	EventSystem();

	void RunEvent(char* _name, GameObject* _gameObject);
	void RunEvent(char* _name, GameObject* _gameObject, char* _context);
	void ListenForEvent(char* _name, std::function<void(GameEvent*)> _func);
	void ListenForEventContext(char* _name, std::function<void(GameEvent*)> _func, char* _context);

private:
	std::vector<EventSub*> subbedEvents;
	std::vector<EventSub*> subbedEventsContext;
};