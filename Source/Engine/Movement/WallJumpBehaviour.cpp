#include "WallJumpBehaviour.h"
#include <iostream>
#include <GameObjects/GameObject.h>

void WallJumpBehaviour::Start() {
	gameObject->checkWalls = true;
}

void WallJumpBehaviour::Update() {
	if (gameObject->IsGrounded) {
		currentWallJump = 0;
	}
	else if 
		(sf::Keyboard::isKeyPressed(jumpKey1) && !key1Pressed ||
		 sf::Keyboard::isKeyPressed(jumpKey2) && !key2Pressed ||
		 sf::Keyboard::isKeyPressed(jumpKey3) && !key3Pressed) 
	{

		if (!isWallJumping) {
			if (gameObject->wallCheck != gameObject->None && currentWallJump < maxWallJumps) {
				isWallJumping = true;
				currentWallJump++;
				if (gameObject->wallCheck != gameObject->Left) {
					currentJumpKickForce = -jumpKickForce;
					currentJumpForce = jumpForce;
				}
				else if (gameObject->wallCheck != gameObject->Right) {
					currentJumpKickForce = jumpKickForce;
					currentJumpForce = jumpForce;
				}
			}
		}
	}

	if (isWallJumping) {
		timer += deltaTime;

		if (timer < jumpDuration) {
			currentJumpForce -= jumpRolloff * deltaTime;
			currentJumpKickForce -= jumpKickRolloff * deltaTime;

			gameObject->MovePosition(currentJumpKickForce * deltaTime, currentJumpForce * deltaTime);

		}
		else {
			isWallJumping = false;
			timer = 0;
		}
	}

	key1Pressed = sf::Keyboard::isKeyPressed(jumpKey1);
	key2Pressed = sf::Keyboard::isKeyPressed(jumpKey2);
	key3Pressed = sf::Keyboard::isKeyPressed(jumpKey3);
}