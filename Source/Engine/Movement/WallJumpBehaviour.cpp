#include "WallJumpBehaviour.h"
#include <iostream>
#include <GameObjects/GameObject.h>

void WallJumpBehaviour::Start() {
	gameObject->checkWalls = true;
}

void WallJumpBehaviour::Update() {

	key1Pressed = sf::Keyboard::isKeyPressed(jumpKey1);
	key2Pressed = sf::Keyboard::isKeyPressed(jumpKey2);
	key3Pressed = sf::Keyboard::isKeyPressed(jumpKey3);
}