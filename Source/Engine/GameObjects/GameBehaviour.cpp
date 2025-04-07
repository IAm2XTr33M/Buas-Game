#include "GameBehaviour.h"
#include <iostream>
#include "GameObject.h"


GameBehaviour::GameBehaviour()
{
}

void GameBehaviour::SetGameObject(GameObject* gameObject) {
	this->gameObject = gameObject;
	events = gameObject->events;
	bodyId = gameObject->bodyId;
}

void GameBehaviour::Enable() {
	enabled = true;
}
void GameBehaviour::Disable() {
	enabled = false;
}
