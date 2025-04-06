#pragma once
class GameObject;

class GameEvent
{
public:
	char* eventName = "Event";
	GameObject* gameObject;
	char* context;
	GameEvent(char* _eventName, GameObject* _gameObject);
	GameEvent(char* _eventName, GameObject* _gameObject, char* _context);
};

