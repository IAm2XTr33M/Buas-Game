#include "AdvancedMovementBehaviour.h"
#include <iostream>
#include <GameObjects/GameObject.h>

void AdvancedMovementBehaviour::Start() {
}

void AdvancedMovementBehaviour::Update() {

	float XInput = 0;
	float YInput = 0;

	if (XMovement) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (moveXNegative < XStartSpeed) {
				moveXNegative = XStartSpeed;
			}
			if (moveXNegative < XMaxSpeed) {
				moveXNegative += (deltaTime / XSecondsToMax) * (XMaxSpeed - XStartSpeed);
				if (moveXNegative > XMaxSpeed) {
					moveXNegative = XMaxSpeed;
				}
			}
		}
		else if (moveXNegative > 0) {
			if (removeXNegative == 0) {
				removeXNegative = moveXNegative;
			}
			moveXNegative -= removeXNegative / XSecondsToZero * deltaTime;
			if (moveXNegative < 0) {
				moveXNegative = 0;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (moveXPositive < XStartSpeed) {
				moveXPositive = XStartSpeed;
			}
			if (moveXPositive < XMaxSpeed) {
				moveXPositive += (deltaTime / XSecondsToMax) * (XMaxSpeed - XStartSpeed);
				if (moveXPositive > XMaxSpeed) {
					moveXPositive = XMaxSpeed;
				}
			}
		}
		else if (moveXPositive > 0) {
			if (removeXPositive == 0) {
				removeXPositive = moveXPositive;
			}
			moveXPositive -= removeXPositive / XSecondsToZero * deltaTime;
			if (moveXPositive < 0) {
				moveXPositive = 0;
			}
		}
	}
	if (YMovement) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (moveYNegative < YStartSpeed) {
				moveYNegative = YStartSpeed;
			}
			if (moveYNegative < YMaxSpeed) {
				moveYNegative += (deltaTime / YSecondsToMax) * (YMaxSpeed - YStartSpeed);
				if (moveYNegative > YMaxSpeed) {
					moveYNegative = YMaxSpeed;
				}
			}
		}
		else if (moveYNegative > 0) {
			if (removeYNegative == 0) {
				removeYNegative = moveYNegative;
			}
			moveYNegative -= removeYNegative / XSecondsToZero * deltaTime;
			if (moveYNegative < 0) {
				moveYNegative = 0;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (moveYPositive < YStartSpeed) {
				moveYPositive = YStartSpeed;
			}
			if (moveYPositive < YMaxSpeed) {
				moveYPositive += (deltaTime / YSecondsToMax) * (YMaxSpeed - YStartSpeed);
				if (moveYPositive > YMaxSpeed) {
					moveYPositive = YMaxSpeed;
				}
			}
		}
		else if (moveYPositive > 0) {
			if (removeYPositive == 0) {
				removeYPositive = moveYPositive;
			}
			moveYPositive -= removeYPositive / XSecondsToZero * deltaTime;
			if (moveYPositive < 0) {
				moveYPositive = 0;
			}
		}
	}

	float finalXMove = moveXPositive - moveXNegative;
	float finalYMove = moveYPositive - moveYNegative;


	if (finalXMove != 0 || finalYMove != 0) {
		gameObject->MovePosition(finalXMove * deltaTime, finalYMove * deltaTime);
	}
}