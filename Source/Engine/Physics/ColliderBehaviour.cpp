#include "ColliderBehaviour.h"
#include <iostream>
#include <GameObjects/GameObject.h>

void ColliderBehaviour::Start() {
    gameObject->hasCollision = true;
}

void ColliderBehaviour::Update() {

}