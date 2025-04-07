#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "GameBehaviour.h"
#include <filesystem>
#include <string>
#include "gameEngine.h"
#include "Events/EventSystem.h"

#include <box2d/box2d.h> 

class GameEngine;

class GameObject {
public:
    // Constructor and Destructor
    GameObject(std::filesystem::path _texturePath, char* _name, float startX, float startY);
    ~GameObject();

    float worldScale = 30.0f;
    void InitPhysics(b2WorldId* id);
    b2BodyId bodyId;


    sf::Vector2f GetPos();
    b2Vec2 GetPosInM();
    void SetPosInM(b2Vec2 pos);
    void SetPos(sf::Vector2f pos);
    
    float GetRot();
    void SetRot(float rot);

    sf::Vector2f GetSize();
    b2Vec2 GetSizeInM();
    void SetSizeInM(b2Vec2 size);
    void SetSize(sf::Vector2f size);

    sf::Vector2f GetCenter() const;


    const sf::Sprite& GetSprite() const;



    // Start Update and Render
    void Start(sf::RenderWindow* window,std::vector<GameObject>* engineGameObjects, GameEngine* _engine);
    void Update(float deltaTime);
    void Render();
    void UpdateSprite();

    bool hasCollision = false;
    bool checkWalls = false;

    void addBehaviour(GameBehaviour* behaviour);
    template <typename T>
    T* GetBehaviour() {
        for (auto* behaviour : behaviours) {
            if (auto* typedBehaviour = dynamic_cast<T*>(behaviour)) {
                return typedBehaviour;
            }
        }
        return nullptr;
    }

    std::vector<GameBehaviour*> behaviours;
    
    GameBehaviour* rigidbody = nullptr;

    char* name = "";
    char* tag = "";

    sf::Vector2f position;
    float rotation = 0;
    sf::Vector2f scale;
    sf::Texture texture;
    int renderLayer = 1;

    std::vector<GameObject>* engineGameObjects;
    GameEngine* engine;

    sf::Sprite sprite;

    sf::RenderWindow* window;

    EventSystem* events;

    float deltaTime = 0;
private:
    bool centerPos = true;


    float groundCheckTimer = 0;
    float wallCheckTimer = 0;
};

#endif // GAMEOBJECT_H
