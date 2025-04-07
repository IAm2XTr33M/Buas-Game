#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include "GameObjects/GameObject.h"
#include <map>
#include "Events/EventSystem.h"
#include "box2d/box2d.h"

class GameEngine {
public:

    GameEngine();
    void Run();
    bool centerPositions = true;
    std::vector<GameObject> gameObjects;
    sf::View view;

    void AddToRenderQueue(sf::Drawable* _drawable, int _layer);
    std::map<sf::Drawable*, int> renderQueue;

    std::map<std::string, int> renderLayers;

    void addLayer(const std::string& layerName, int layerValue) {
        renderLayers[layerName] = layerValue;
    }

    int& operator[](const std::string& layerName) {
        return renderLayers[layerName];
    }

    EventSystem* events = new EventSystem();

    float targetFPS = 5.0f;
    b2WorldId worldId;

private:
    void ProcessEvents();
    void Update(float deltaTime);
    void Render();

    sf::RenderWindow window;
    sf::Clock clock;

    float currentTime = 0;
    int currentFrame = 0;
};

#endif // GAMEENGINE_H
