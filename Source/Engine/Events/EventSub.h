#pragma once
#include "Events/GameEvent.h"
#include "functional"

class EventSub
{
public:
	EventSub(char* _name, std::function<void(GameEvent*)> _func);
	EventSub(char* _name, std::function<void(GameEvent*)> _func, char* _context);
	
	char* name;
	std::function<void(GameEvent*)> func;
	char* context;
};

