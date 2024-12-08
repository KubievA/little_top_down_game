#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

//_______________________________________________________________________---------

int main()
{
    // Window dimensions
    int windowDimension[2];
    windowDimension[0] = 400; // WIDTH
    windowDimension[1] = 400; // HEIGHT
    // initialize the window
    InitWindow(windowDimension[0], windowDimension[1], "Andis Top Down");

    // Map texture---
    Texture2D Map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");

    // outside the loop to save the value in between the iteraton of the loop
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight{windowDimension[0], windowDimension[1]};


    Prop props[2]{
        Prop{Vector2{600.f,300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f,500.f}, LoadTexture("nature_tileset/Log.png")}
    };


    Enemy goblin{
        Vector2{800.f,300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy slime{
        Vector2{500.f,700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[]{
        &goblin,
        &slime
    };

    // sets the Target to knight
    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

//_______________________________________________________________________ --------
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //start drawing
        BeginDrawing();
        ClearBackground(WHITE);

//_______________________________________________________________________

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f) ;

        // draw the map
        DrawTextureEx(Map, mapPos, 0.0, mapScale, WHITE);

        // draw the props
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }


        if (!knight.getAlive()) // Character is not alive
        {
            DrawText("Game Over", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else // Character is alive
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0.f, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40.f, RED);
        }



        // draw the knight
        knight.tick(GetFrameTime());


        // Check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowDimension[0] > Map.width * mapScale ||
            knight.getWorldPos().y + windowDimension[1] > Map.height * mapScale)
        {
            knight.undoMovement();
        }

        // check prop collisions
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.GetCollisionRec(knight.getWorldPos()), knight.GetCollisionRec()) )
            {
                knight.undoMovement();
            }
        }

        // draw the enemy
        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }


        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->GetCollisionRec(), knight.getWeoponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }


        }


//_______________________________________________________________________

        // stop drawing
        EndDrawing();
    }

    UnloadTexture(Map);
    CloseWindow();
}