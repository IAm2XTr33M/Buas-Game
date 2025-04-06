#pragma once 
#include <GameObjects/GameBehaviour.h>
class AdvancedMovementBehaviour : public GameBehaviour
{
public:
	void Start() override;
	void Update() override;

	bool XMovement = true;
	bool YMovement = true;

	float XStartSpeed = 100;
	float YStartSpeed = 100;

	float XMaxSpeed = 1000;
	float YMaxSpeed = 1000;

	float XSecondsToMax = 1;
	float YSecondsToMax = 1;

	float XSecondsToZero = 10;
	float YSecondsToZero = 10;

private:
	float moveXPositive = 0;
	float moveXNegative = 0;
	float moveYPositive = 0;
	float moveYNegative = 0;

	float removeXPositive = 0;
	float removeXNegative = 0;
	float removeYPositive = 0;
	float removeYNegative = 0;

};
