#pragma once
class GameObject;
class EventSystem;

#include "Events/EventSub.h"
#include "Events/GameEvent.h"

class GameBehaviour
{
public:
	GameBehaviour();
	virtual void Update() {};
	virtual void Start() {};

	virtual void Enable();
	virtual void Disable();

	bool enabled = true;
	float deltaTime = 0;

	void SetGameObject(GameObject* gameObject);

	GameObject* gameObject;
	EventSystem* events;

	template <typename ClassType, typename ArgType>
	auto call(void (ClassType::* func)(ArgType), ClassType* instance) {
		return [instance, func](ArgType arg) {
			(instance->*func)(arg);
			};
	}
};