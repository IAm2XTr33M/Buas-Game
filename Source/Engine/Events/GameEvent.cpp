#include "GameEvent.h"

GameEvent::GameEvent(char* _eventName, GameObject* _gameObject) {
	eventName = _eventName;
	gameObject = _gameObject;
}

GameEvent::GameEvent(char* _eventName, GameObject* _gameObject, char* _context) {
	eventName = _eventName;
	gameObject = _gameObject;
	context = _context;
}