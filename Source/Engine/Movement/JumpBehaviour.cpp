#include "JumpBehaviour.h"
#include <GameObjects/GameObject.h>
#include <Physics/GravityBehaviour.h>
#include <iostream>

JumpBehaviour::JumpBehaviour(){
}

void JumpBehaviour::Start() {
	events->ListenForEvent("Jump Event", call(&JumpBehaviour::test,this));
}

void JumpBehaviour::test(GameEvent* _event) {
	std::cout << _event->eventName << " From: " << _event->gameObject->name << std::endl;
}

void JumpBehaviour::Update() {

	//Check for jump input key
	//jump if
	//you are grounded (start at jump 0)
	//you are in the air, have gone up AND jump < maxJumps



	if (sf::Keyboard::isKeyPressed(jumpKey1) && !key1Pressed || 
		sf::Keyboard::isKeyPressed(jumpKey2) && !key2Pressed ||
		sf::Keyboard::isKeyPressed(jumpKey3) && !key3Pressed) {

		
		if (canTryJump) {


			canTryJump = false;

/*			if (gameObject->IsGrounded) {
				currentJumpForce = jumpForce;
				currentJumpAmount = 1;
				jump = true;
			}
			else */if(currentJumpAmount > 0 && currentJumpAmount < maxJumpAmount) {
				jumpTimer = 0;
				currentJumpForce = jumpForce;
				currentJumpAmount++;
				gameObject->GetBehaviour<GravityBehaviour>()->velocity = 0;
				jump = true;
			}
			else {
				canTryJump = true;
			}
		}
	}

	if (jump) {
		jumpTimer += deltaTime;

		currentJumpForce -= jumpRolloff * deltaTime;

		//gameObject->MovePosition(0, currentJumpForce * deltaTime);
		
		canTryJump = true;

		if (jumpTimer >= jumpDuration) {
			jump = false;
			jumpTimer = 0;
		}
	}

	key1Pressed = sf::Keyboard::isKeyPressed(jumpKey1);
	key2Pressed = sf::Keyboard::isKeyPressed(jumpKey2);
	key3Pressed = sf::Keyboard::isKeyPressed(jumpKey3);
}