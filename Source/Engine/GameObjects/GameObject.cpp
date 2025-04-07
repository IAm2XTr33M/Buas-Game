#include "GameObject.h"
#include <iostream>
#include <Physics/PhysicsBehaviour.h>

GameObject::GameObject(const std::filesystem::path  _texturePath, char* _name, float _startX, float _startY) {
    name = _name;
    if (texture.loadFromFile(_texturePath.generic_string())) {
        sprite.setTexture(texture);
    }
    else {
        std::cout << "Texture at path " << _texturePath << " is not valid" << std::endl;
    }
    position = sf::Vector2f(_startX, _startY);

    std::cout << "Created " << _name << " Position " << position.x << ":" << position.y << std::endl;
    rotation = 0;

    sf::Vector2u textureSize = texture.getSize();
    scale = { static_cast<float>(textureSize.x), static_cast<float>(textureSize.y) };

    UpdateSprite();
}
GameObject::~GameObject() {}

void GameObject::InitPhysics(b2WorldId* worldId) {

    PhysicsBehaviour* physics = GetBehaviour<PhysicsBehaviour>();

    b2Vec2 startPos = GetPosInM(); 
    b2Vec2 size = GetSizeInM();
    b2BodyDef body = b2DefaultBodyDef();

    body.name = name;
    body.isEnabled = true;
    body.position = startPos;

    b2ShapeDef shapeDef = b2DefaultShapeDef();

    if (physics != nullptr) {
        body.type = physics->isStatic ? b2_staticBody : b2_dynamicBody;
        body.gravityScale = physics->useGravity ? physics->gravityScale : 0.0f;
        bodyId = b2CreateBody(*worldId, &body);

        shapeDef.density = physics->shapeDensity;
        shapeDef.friction = physics->shapeFriction;

        if (physics->shape == PhysicsBehaviour::Shape::Box) {
            std::cout << "CREATED Box" << std::endl;

            b2Polygon polygon = b2MakeBox(size.x / 2, size.y / 2);
            b2CreatePolygonShape(bodyId, &shapeDef, &polygon);
        }
        else if (physics->shape == PhysicsBehaviour::Shape::Circle) {
            std::cout << "CREATED CIRCLE" << std::endl;
            b2Circle circleData = { b2Vec2{0,0}, GetSizeInM().x / 2 }; 
            b2CreateCircleShape(bodyId, &shapeDef, &circleData); 
        }

    }
    else {
        std::cout << "CREATED default" << std::endl;

        body.type = b2_staticBody;

        bodyId = b2CreateBody(*worldId, &body);

        shapeDef.density = 1.0f;
        std::cout << size.x << ":" << size.y << std::endl;
        b2Polygon polygon = b2MakeBox(size.x / 2, size.y / 2);
        b2CreatePolygonShape(bodyId, &shapeDef, &polygon);
    }
}

void GameObject::SetPosInM(b2Vec2 _pos) {
    if (centerPos) {
        position = sf::Vector2(_pos.x * worldScale - scale.x / 2, _pos.y * worldScale - scale.y / 2);
    }
    else {
        position = sf::Vector2(_pos.x * worldScale, _pos.y * worldScale);
    }
}

b2Vec2 GameObject::GetPosInM() {
    return { position.x / worldScale, position.y / worldScale };
}

b2Vec2 GameObject::GetSizeInM() {
    std::cout << scale.x << ":" << scale.y << std::endl;

    return { scale.x / worldScale, scale.y / worldScale };
}

sf::Vector2f GameObject::GetCenter() const {
    return sf::Vector2f(position.x + scale.x / 2,
        position.y + scale.y / 2);
}

const sf::Sprite& GameObject::GetSprite() const {
    return sprite;
}


void GameObject::Start(sf::RenderWindow* _window, std::vector<GameObject>* _engineGameObjects, GameEngine* _engine) {
    engineGameObjects = _engineGameObjects;
    window = _window;
    engine = _engine;
    centerPos = _engine->centerPositions;
    for (auto& obj : behaviours) {
        obj->SetGameObject(this);
        obj->Start();
    }
}

void GameObject::Update(float _deltaTime) {
    deltaTime = _deltaTime;

    for (auto& obj : behaviours) {
        if (obj->enabled) {
            obj->Update();
            obj->deltaTime = _deltaTime;
        }
    }

    b2Vec2 currentPos = b2Body_GetPosition(bodyId);
    SetPosInM(currentPos);
    std::cout << position.y << std::endl;
}


// Render the sprite
void GameObject::Render() {
    UpdateSprite();

    engine->AddToRenderQueue(&sprite, renderLayer);
}

void GameObject::UpdateSprite() {
    sprite.setPosition(position);
    sprite.setRotation(this->rotation);
    sprite.setTexture(texture);
}

void GameObject::addBehaviour(GameBehaviour* behaviour) {
    // Set the GameObject reference for each behaviour
    behaviour->SetGameObject(this);
    behaviours.push_back(behaviour);

    if (dynamic_cast<PhysicsBehaviour*>(behaviour)) {
        std::cout << "added the bahaviour" << std::endl;
    }
}

