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
    GameObject();
    GameObject(const sf::Texture& texture);
    GameObject(const sf::Texture& texture, char* _name);
    GameObject(const sf::Texture& texture, float startX, float startY);
    GameObject(const sf::Texture& texture, char* _name, float startX, float startY);
    GameObject(std::filesystem::path _texturePath, char* _name, float startX, float startY);
    ~GameObject();

    void InitPhysics(b2WorldId& id);
    b2BodyId myBodyId;

    //Changers
    void MovePosition(sf::Vector2f position);
    void MovePosition(float posX, float posY);
    void Rotate(float rotation);
    void ChangeScale(float scale);
    void ChangeScale(float scaleX, float scaleY);
    void ChangeScale(sf::Vector2f scale);

    // Getters
    sf::Vector2f GetPosition() const;
    sf::Vector2f GetCenter() const;
    float GetRotation() const;
    sf::Vector2f GetScale() const;
    const sf::Sprite& GetSprite() const;

    void SetScale(float scale);
    void SetScale(float scaleX, float scaleY);
    void SetScale(sf::Vector2f scale);


    // Start Update and Render
    void Start(sf::RenderWindow* window,std::vector<GameObject>* engineGameObjects, GameEngine* _engine);
    void Update(float deltaTime);
    void Render();
    void UpdateSprite();

    bool hasCollision = false;
    bool checkWalls = false;

    void CheckGround(bool speedup = false);
    char* groundTag = "ground";
    float groundCheckDistance = 1;
    float groundChecksPerSecond = 15;
    bool IsGrounded = false;

    void CheckWall(bool speedup = false);
    char* wallTag = "wall";
    float wallCheckDistance = 1;
    float wallChecksPerSecond = 15;
    enum Walls { None,Left,Right };
    Walls wallCheck = None;

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

    float groundCheckTimer = 0;
    float wallCheckTimer = 0;
};

#endif // GAMEOBJECT_H
