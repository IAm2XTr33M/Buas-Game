#include "EventSub.h"

EventSub::EventSub(char* _name, std::function<void(GameEvent*)> _func)
{
	name = _name;
	func = _func;
}

EventSub::EventSub(char* _name, std::function<void(GameEvent*)> _func, char* _context)
{
	name = _name;
	func = _func;
	context = _context;
}