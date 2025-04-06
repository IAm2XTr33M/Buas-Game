#include "GameObject.h"
#include <iostream>

GameObject::GameObject() {
    position = sf::Vector2f(0, 0);
    rotation = 0;
    scale = sf::Vector2f(1.0f, 1.0f);
    UpdateSprite();
}
GameObject::GameObject(const sf::Texture& _texture) {
    texture = _texture;
    position = sf::Vector2f(50, 50);
    rotation = 0;
    scale = sf::Vector2f(1.0f, 1.0f);
    UpdateSprite();
}
GameObject::GameObject(const sf::Texture& _texture, char* _name) {
    name = _name;
    texture = _texture;
    position = sf::Vector2f(50, 50);
    rotation = 0;
    scale = sf::Vector2f(1.0f, 1.0f);

    UpdateSprite();
}
GameObject::GameObject(const sf::Texture& _texture, float _startX, float _startY) {
    texture = _texture;
    position = sf::Vector2f(50, 50);
    rotation = 0;
    scale = sf::Vector2f(1.0f, 1.0f);

    UpdateSprite();
}
GameObject::GameObject(const sf::Texture& _texture, char* _name, float _startX, float _startY) {
    name = _name;
    texture = _texture;

    position = sf::Vector2f(_startX, _startY);

    std::cout << "Created " << _name << " Position " << _startX  << std::endl;
    rotation = 0;
    scale = sf::Vector2f(1.0f, 1.0f);

    UpdateSprite();
}
GameObject::GameObject(const std::filesystem::path  _texturePath, char* _name, float _startX, float _startY) {
    name = _name;
    if (texture.loadFromFile(_texturePath.generic_string())) {
        sprite.setTexture(texture);
    }
    else {
        std::cout << "Texture at path " << _texturePath << " is not valid" << std::endl;
    }

    position = sf::Vector2f(_startX, _startY);

    std::cout << "Created " << _name << " Position " << _startX << std::endl;
    rotation = 0;
    scale = sf::Vector2f(1.0f, 1.0f);

    UpdateSprite();
}

GameObject::~GameObject() {}

void GameObject::InitPhysics() {
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.isEnabled = true;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{position.x, position.y};

    myBodyId = b2CreateBody(engine->worldId, &bodyDef);
    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);

    b2ShapeDef shapedef = b2DefaultShapeDef();
    shapedef.density = 1.0f;
    shapedef.friction = 0.3f;

    b2CreatePolygonShape(myBodyId, &shapedef, &dynamicBox);
}

// Changers
void GameObject::MovePosition(sf::Vector2f _position) {    
    if (hasCollision) {
        CheckGround(true);

        sf::FloatRect spriteBounds = sprite.getGlobalBounds();
        sf::RectangleShape boundingBox_X;
        boundingBox_X.setSize(sf::Vector2f(spriteBounds.width, spriteBounds.height));
        boundingBox_X.setPosition(spriteBounds.left + _position.x, spriteBounds.top);
        sf::RectangleShape boundingBox_Y;
        boundingBox_Y.setSize(sf::Vector2f(spriteBounds.width, spriteBounds.height));
        boundingBox_Y.setPosition(spriteBounds.left, spriteBounds.top - _position.y);

        bool canMoveX = true;
        bool canMoveY = true;

        for (auto& obj : *engineGameObjects) {
            if (obj.hasCollision && &obj != this) {

                if (boundingBox_X.getGlobalBounds().intersects(obj.sprite.getGlobalBounds())) {
                    canMoveX = false;
                }
                if (boundingBox_Y.getGlobalBounds().intersects(obj.sprite.getGlobalBounds())) {
                    canMoveY = false;
                }
            }
        }

        if (canMoveX == false && canMoveY == false) {
            if (_position.x < _position.y) {
                _position.x = -_position.x;
                canMoveX = true;
            }
            else {
                _position.y = -_position.y;
                canMoveY = true;
            }
        }

        if (canMoveX) {
            sf::Vector2f currentPos = GetPosition();
            position = sf::Vector2f(currentPos.x + _position.x, currentPos.y);
        }        
        if (canMoveY) {
            sf::Vector2f currentPos = GetPosition();
            position = sf::Vector2f(currentPos.x, currentPos.y - _position.y);
        }

    }
    else {
        sf::Vector2f currentPos = GetPosition();
        position = sf::Vector2f(currentPos.x + _position.x, currentPos.y - _position.y);
    }
}
void GameObject::MovePosition(float posX, float posY) {
    MovePosition(sf::Vector2f(posX, posY));
}
void GameObject::Rotate(float _rotation) {
    float currentRotation = GetRotation();
    rotation = currentRotation + _rotation;
}
void GameObject::ChangeScale(float scale) {
    ChangeScale(sf::Vector2f(scale, scale));
}
void GameObject::ChangeScale(float scaleX, float scaleY) {
    ChangeScale(sf::Vector2f(scaleX, scaleY));
}
void GameObject::ChangeScale(sf::Vector2f _scale) {
    sf::Vector2f currentScale = GetScale();
    scale = currentScale + _scale;
}

// Getters
sf::Vector2f GameObject::GetPosition() const {
    return position;
}
sf::Vector2f GameObject::GetCenter() const {
    
    return sf::Vector2f(position.x + sprite.getGlobalBounds().width / 2, 
                        position.y + sprite.getGlobalBounds().height / 2);
}

float GameObject::GetRotation() const {
    return rotation;
}

sf::Vector2f GameObject::GetScale() const {
    return scale;
}

const sf::Sprite& GameObject::GetSprite() const {
    return sprite;
}

void GameObject::SetScale(float scale) {
    ChangeScale(sf::Vector2f(scale, scale));
}
void GameObject::SetScale(float scaleX, float scaleY) {
    ChangeScale(sf::Vector2f(scaleX, scaleY));
}
void GameObject::SetScale(sf::Vector2f _scale) {
    scale = _scale;
}



void GameObject::CheckGround(bool speedup) {

    float delayBetween = 1 / groundChecksPerSecond;

    if (speedup) {
        groundCheckTimer += deltaTime * 6;
    }
    else {
        groundCheckTimer += deltaTime;
    }


    if (groundCheckTimer > delayBetween) {
        groundCheckTimer = 0;
        
        //perform ground check

        sf::FloatRect spriteBounds = sprite.getGlobalBounds();
        sf::RectangleShape groundCheckShape;
        groundCheckShape.setSize(sf::Vector2f(spriteBounds.width, spriteBounds.height));
        groundCheckShape.setPosition(spriteBounds.left, spriteBounds.top + groundCheckDistance);

        bool isOnGround = false;

        for (auto& obj : *engineGameObjects) {
            if (obj.hasCollision && &obj != this) {
                if (obj.tag == groundTag) {
                    if (groundCheckShape.getGlobalBounds().intersects(obj.sprite.getGlobalBounds())) {
                        isOnGround = true;
                        break;
                    }
                }
            }
        }

        IsGrounded = isOnGround;
    }
}

void GameObject::CheckWall(bool speedup) {

    float delayBetween = 1 / wallChecksPerSecond;

    if (speedup) {
        wallCheckTimer += deltaTime * 6;
    }
    else {
        wallCheckTimer += deltaTime;
    }


    if (wallCheckTimer > delayBetween) {
        wallCheckTimer = 0;

        //perform wall check

        sf::FloatRect spriteBounds = sprite.getGlobalBounds();

        sf::RectangleShape wallCheckShapeLeft;
        wallCheckShapeLeft.setSize(sf::Vector2f(spriteBounds.width, spriteBounds.height));
        wallCheckShapeLeft.setPosition(spriteBounds.left - wallCheckDistance, spriteBounds.top);

        sf::RectangleShape wallCheckShapeRight;
        wallCheckShapeRight.setSize(sf::Vector2f(spriteBounds.width, spriteBounds.height));
        wallCheckShapeRight.setPosition(spriteBounds.left + wallCheckDistance, spriteBounds.top);

        Walls isOnWall = None;

        for (auto& obj : *engineGameObjects) {
            if (obj.hasCollision && &obj != this) {
                if (obj.tag == wallTag) {
                    if (wallCheckShapeLeft.getGlobalBounds().intersects(obj.sprite.getGlobalBounds())) {
                        isOnWall = Left;
                        break;
                    }
                    if (wallCheckShapeRight.getGlobalBounds().intersects(obj.sprite.getGlobalBounds())) {
                        isOnWall = Right;
                        break;
                    }
                }
            }
        }

        wallCheck = isOnWall;
    }
}


void GameObject::Start(sf::RenderWindow* _window, std::vector<GameObject>* _engineGameObjects, GameEngine* _engine) {
    engineGameObjects = _engineGameObjects;
    window = _window;
    engine = _engine;
    for (auto& obj : behaviours) {
        obj->SetGameObject(this);
        obj->Start();
    }
}

void GameObject::Update(float _deltaTime) {
    deltaTime = _deltaTime;
    std::cout << "Position: " << b2Body_GetPosition(myBodyId).x << " : " << b2Body_GetPosition(myBodyId).y << std::endl;
    for (auto& obj : behaviours) {
        if (obj->enabled) {
            obj->Update();
            obj->deltaTime = _deltaTime;
        }
    }
    if (hasCollision) {
        CheckGround();
    }
    if (checkWalls) {
        CheckWall();
    }
}



// Render the sprite
void GameObject::Render() {
    UpdateSprite();

    engine->AddToRenderQueue(&sprite, renderLayer);
}

void GameObject::UpdateSprite() {
    sprite.setPosition(this->position);
    sprite.setRotation(this->rotation);
    sprite.setScale(scale);
    sprite.setTexture(texture);
}

void GameObject::addBehaviour(GameBehaviour* behaviour) {
    // Set the GameObject reference for each behaviour
    behaviour->SetGameObject(this);
    behaviours.push_back(behaviour);
}

