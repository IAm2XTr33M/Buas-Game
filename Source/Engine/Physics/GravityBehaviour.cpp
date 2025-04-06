#include "GravityBehaviour.h"
#include <iostream>
#include <GameObjects/GameObject.h>

void GravityBehaviour::Start() {
}

void GravityBehaviour::Update() {
	if (!gameObject->IsGrounded) {
		velocity = velocity + (gravityScale / 100);
		velocity += velocity * gravityMultiplier * deltaTime;
		velocity = velocity > gravityScale * maxGravity ? gravityScale * maxGravity : velocity;

		gameObject->MovePosition(sf::Vector2f(0, -velocity * deltaTime));
	}
	else {
		velocity = 0;
	}
}