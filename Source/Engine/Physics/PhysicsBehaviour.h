#pragma once
#include <GameObjects/GameBehaviour.h>
#include <SFML/Graphics.hpp>
class PhysicsBehaviour : public GameBehaviour
{
public:
	void Start() override;
	void Update() override;

	bool isStatic = false; //als false dynamic body
	bool useGravity = true;
	float gravityScale = 1.0f;

	enum Shape{Box,Circle};
	PhysicsBehaviour::Shape shape = Box;

	float shapeDensity = 1.0f;
	float shapeFriction = 1.0f;
};
