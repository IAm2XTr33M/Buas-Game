#pragma once 
#include <GameObjects/GameBehaviour.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>

class JumpBehaviour : public GameBehaviour
{
public:
	JumpBehaviour();

	void Start() override;
	void Update() override;
	sf::Keyboard::Key jumpKey1 = sf::Keyboard::Space;
	sf::Keyboard::Key jumpKey2 = sf::Keyboard::Up;
	sf::Keyboard::Key jumpKey3 = sf::Keyboard::W;
	float jumpDuration = 0.4;
	float jumpRolloff = 400;
	float jumpForce = 400;
	int maxJumpAmount = 1;
	void test(GameEvent* _event);
	 

private:
	float currentJumpForce = 0;
	bool canTryJump = true;
	bool jump = false;
	int currentJumpAmount = 0;
	float jumpTimer = 0;

	bool key1Pressed = false;
	bool key2Pressed = false;
	bool key3Pressed = false;
};
