#pragma once
#include "MovementBehaviour.h"
#include <SFML/Graphics.hpp>
#include <GameObjects/GameObject.h>

void MovementBehaviour::Start() {
}

void MovementBehaviour::Update() {

	Xmove = 0;
	Ymove = 0;
	
	if (movementEnabled_X) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			Xmove -= speed;

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			Xmove += speed;
		}
	}
	if (movementEnabled_y) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			Ymove -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			Ymove += speed;
		}
	}

	if (Xmove != 0 || Ymove != 0) {
		b2Body_ApplyForceToCenter(bodyId, {Xmove, Ymove},true);
	}
}