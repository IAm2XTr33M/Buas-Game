#pragma once
#include <GameObjects/GameBehaviour.h>
class MovementBehaviour : public GameBehaviour
{
public:
	void Start() override;
	void Update() override;
	float speed = 10;
	bool movementEnabled_X = true;
	bool movementEnabled_y = true;

private:
	float Xmove = 0;
	float Ymove = 0;
};

