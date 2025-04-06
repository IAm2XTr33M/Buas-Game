#pragma once 
#include <GameObjects/GameBehaviour.h>
class GravityBehaviour : public GameBehaviour
{
public:
	void Start() override;
	void Update() override;
	float gravityScale = 0;
	float gravityMultiplier = 2;
	float velocity = 0;
	float maxGravity = 10;
};
