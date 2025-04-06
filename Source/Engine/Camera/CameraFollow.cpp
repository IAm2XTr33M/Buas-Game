#include "CameraFollow.h"
#include <GameObjects/GameObject.h>
#include <GameEngine.h>
#include <IOSTREAM>

void CameraFollow::Start() {
	view = &gameObject->engine->view;
	previousPosition = gameObject->position;
}

void CameraFollow::Update() {
	
	if (previousPosition != gameObject->position) {
		sf::Vector2f position;
		if (center) {
			position = gameObject->GetCenter() + offset;
		}
		else {
			position = gameObject->position + offset;
		}

		if (useMinY) {
			position.y = position.y < minY ? minY : position.y;
		}
		if (useMaxY) {
			position.y = position.y > maxY ? maxY : position.y;
		}
		
		if (useMinX) {
			position.x = position.x < minX ? minX : position.x;
		}
		if (useMaxX) {
			position.x = position.x > maxX ? maxX : position.x;
		}

		view->setCenter(position);


		gameObject->window->setView(*view);
	}

	previousPosition = gameObject->position;
}
