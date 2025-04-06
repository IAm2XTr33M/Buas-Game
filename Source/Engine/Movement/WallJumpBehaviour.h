#pragma once
#include <GameObjects/GameBehaviour.h>
#include <SFML/Window/Keyboard.hpp>

class WallJumpBehaviour : public GameBehaviour
{
public:
	void Start() override;
	void Update() override;
	sf::Keyboard::Key jumpKey1 = sf::Keyboard::Space;
	sf::Keyboard::Key jumpKey2 = sf::Keyboard::Up;
	sf::Keyboard::Key jumpKey3 = sf::Keyboard::W;

	float jumpDuration = 0.25;
	float jumpRolloff = 450;
	float jumpForce = 500;
	float jumpKickForce = 400;
	float jumpKickRolloff = 450;
	int maxWallJumps = 1;

private:
	bool key1Pressed = false;
	bool key2Pressed = false;
	bool key3Pressed = false;

	bool isWallJumping = false;
	float timer = 0;
	float currentJumpForce = 0;
	float currentJumpKickForce = 0;
	int currentWallJump = 0;
};

