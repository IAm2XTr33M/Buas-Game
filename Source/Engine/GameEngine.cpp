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
    worldDef.gravity = { 10.0f, 10.0f };
    worldId = b2CreateWorld(&worldDef);

    std::cout << worldId.index1 << std::endl;


    view = window.getDefaultView();

    for (auto& obj : gameObjects) {
        obj.engine = this;
        obj.events = events;
        obj.InitPhysics();
        obj.Start(&window ,&gameObjects, this);
    }

    while (window.isOpen()) {
        ProcessEvents();
        float deltaTime = clock.restart().asSeconds();
        Update(deltaTime);
        Render();
    }
}

void GameEngine::ProcessEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            b2DestroyWorld(worldId);
            window.close();
        }
    }
}

void GameEngine::Update(float deltaTime) {
    //hier update doen
    currentTime += deltaTime;
    currentFrame++;

    b2World_Step(worldId, timeStep, 4);
    
    //std::cout << b2World_IsValid(worldId) << std::endl;

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


