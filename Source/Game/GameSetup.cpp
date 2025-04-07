#include "GameSetup.h"
#include "GameEngine.h"

GameSetup::GameSetup()
{
    GameEngine engine;
   
    engine.centerPositions = false;
    engine.targetFPS = 100;

    engine.renderLayers = {
        {"foreground" , 2},
        {"background" , -1}
    };

    {
        GameObject obj("assets/TestPlayer.png", "player", 0, 0);

        obj.renderLayer = engine.renderLayers["foreground"];

        CameraFollow follow;
        obj.addBehaviour(&follow);

        MovementBehaviour movement;
        movement.speed = 1000;
        movement.movementEnabled_y = false;
        obj.addBehaviour(&movement);

        PhysicsBehaviour physics;
        physics.gravityScale = 1;
        obj.addBehaviour(&physics);

        engine.gameObjects.push_back(obj);
    }

    {
        GameObject obj("assets/TestPlayer.png", "ground", 0, 500);

        obj.renderLayer = engine.renderLayers["foreground"];

        engine.gameObjects.push_back(obj);
    }

    
    {
        
        GameObject obj("assets/TestWall.png", "WallRight", 750, 50);

        ColliderBehaviour collider;
        obj.addBehaviour(&collider);

        GravityBehaviour gravity;
        gravity.gravityScale = 100;
        obj.addBehaviour(&gravity);

        //engine.gameObjects.push_back(obj);
    }


    {
        GameObject obj("assets/TestFloor.png", "Floor", -600, 650);

        ColliderBehaviour collider;
        obj.addBehaviour(&collider);

        
        //engine.gameObjects.push_back(obj);
    }


    {
        GameObject obj("assets/background.png", "background", -600, -200);
        obj.renderLayer = engine.renderLayers["background"];

        //engine.gameObjects.push_back(obj);
    }

    engine.Run();

}
