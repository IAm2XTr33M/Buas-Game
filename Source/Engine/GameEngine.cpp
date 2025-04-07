#include "GameEngine.h"
#include <../Game/GameSetup.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Physics/GravityBehaviour.h>
#include <map>

#include "Box2D/box2d.h"

GameEngine::GameEngine() : window(sf::VideoMode(1280, 720), "Game Engine") {}

void GameEngine::Run() {
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = { 0.0f, 9.8f };
    worldId = b2CreateWorld(&worldDef);

    view = window.getDefaultView();

    for (auto& obj : gameObjects) {
        obj.engine = this;
        obj.events = events;
        obj.InitPhysics(&worldId);
        obj.Start(&window ,&gameObjects, this);
    }

    float frameTimer = 0;

    while (window.isOpen()) {
        ProcessEvents();
        float deltaTime = clock.restart().asSeconds();

        frameTimer += deltaTime;
        if (frameTimer >= 1.0f / targetFPS) {
            frameTimer = frameTimer - 1.0f / targetFPS;

            Update(deltaTime);
            Render();
            b2World_Step(worldId, 1.0f / targetFPS, 4);
        }
    }
}

void GameEngine::ProcessEvents() {
    sf::Event event; 
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void GameEngine::Update(float deltaTime) {
    //hier update doen
    currentTime += deltaTime;
    currentFrame++;

    //std::cout << 
    //    " WorldId: " << worldId.generation <<  
    //    " Gravity: " << b2World_GetGravity(worldId).y <<
    //    " Awake Bodies: " << b2World_GetAwakeBodyCount(worldId) <<
    //std::endl;

    for (auto& obj : gameObjects) {
        obj.Update(deltaTime);
    }
}


bool compareByValue(const std::pair<sf::Drawable*, int>& a, const std::pair<sf::Drawable*, int>& b) {
    return a.second < b.second;
}

void GameEngine::Render() {
    window.clear();
    for (auto& obj : gameObjects) {
        obj.Render();
    }


    //SortRender
    std::vector<std::pair<sf::Drawable*, int>> sortedQueue(renderQueue.begin(), renderQueue.end());
    
    std::sort(sortedQueue.begin(), sortedQueue.end(), compareByValue);

    for (const auto& drawable : sortedQueue) { 
        //std::cout << drawable.first << std::endl;
        window.draw(*drawable.first);
    }

    window.display();
    renderQueue.clear();
}

void GameEngine::AddToRenderQueue(sf::Drawable* _drawable, int _layer) {
    renderQueue.insert(std::pair<sf::Drawable*, int>(_drawable, _layer));
}


