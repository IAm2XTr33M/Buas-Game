#pragma once
#include <GameObjects/GameBehaviour.h>
#include <SFML/Graphics.hpp>

class CameraFollow : public GameBehaviour
{
public:
	void Start() override;
	void Update() override;
	sf::View* view;
	bool center = true;
	sf::Vector2f offset = sf::Vector2f(0,0);
	
	bool useMinY = false;
	bool useMaxY = false;

	float minY = 0;
	float maxY = 0;

	bool useMinX = false;
	bool useMaxX = false;

	float minX = 0;
	float maxX = 0;
private:
	sf::Vector2f previousPosition;
};

