#include "GameSetup.h"
#include "GameEngine.h"

GameSetup::GameSetup()
{
    GameEngine engine;
    
    engine.renderLayers = {
        {"foreground" , 2},
        {"background" , -1}
    };

    {
        GameObject obj("assets/TestPlayer.png", "player", 0, 50);

        obj.renderLayer = engine.renderLayers["foreground"];

        GravityBehaviour gravity;
        gravity.gravityScale = 30;
        gravity.maxGravity = 48;
        obj.addBehaviour(&gravity);

        MovementBehaviour movement;
        movement.speed = 450;
        movement.movementEnabled_y = false;
        obj.addBehaviour(&movement);

        JumpBehaviour jumping;
        jumping.jumpForce = 600;
        jumping.maxJumpAmount = 1;
        obj.addBehaviour(&jumping);

        WallJumpBehaviour wallJumping;
        wallJumping.maxWallJumps = 3;
        wallJumping.jumpForce = 800;
        obj.addBehaviour(&wallJumping);

        ColliderBehaviour collider;
        obj.addBehaviour(&collider);

        DebugBehaviour debugger;
        obj.addBehaviour(&debugger);

        CameraFollow follow;
        follow.useMaxY = true;
        follow.maxY = 320;
        follow.useMinX = true;
        follow.minX = 50;
        obj.addBehaviour(&follow);

        engine.gameObjects.push_back(obj);
    }

    {
        GameObject obj("assets/TestWall.png", "WallRight", 750, 50);

        ColliderBehaviour collider;
        obj.addBehaviour(&collider);

        GravityBehaviour gravity;
        gravity.gravityScale = 100;
        obj.addBehaviour(&gravity);

        obj.tag = obj.wallTag;

        //engine.gameObjects.push_back(obj);
    }


    {
        GameObject obj("assets/TestFloor.png", "Floor", -600, 650);

        ColliderBehaviour collider;
        obj.addBehaviour(&collider);

        obj.tag = obj.groundTag;

        //engine.gameObjects.push_back(obj);
    }


    {
        GameObject obj("assets/background.png", "background", -600, -200);
        obj.renderLayer = engine.renderLayers["background"];

        obj.ChangeScale(0, -0.185f);

        //engine.gameObjects.push_back(obj);
    }

    engine.Run();

}
