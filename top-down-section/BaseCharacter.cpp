#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}


void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
  return Rectangle{
      getScreenPos().x,
      getScreenPos().y,
      width * scale,
      height * scale
  };
}


void BaseCharacter::tick(float deltaTime)
{
  worldPosLastFrame = worldPos;

// update animation frame
  runningTime += deltaTime;
  if(runningTime >= updateTime)
  {
    frame++;
    runningTime = 0.f;
    if (frame > maxFrame) frame = 0;
  }

// returns a float, representing how long that Vector is
  if (Vector2Length(velocity) != 0.0) // checking if it is not equal to zero
  {
      // set worldPos = worldPos + velocity | Vector2Normalize normalizes the speed for the corners
      worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
      // this is a short hand for an if statement with this ? only operator that works on 3 arguments
      // IF (velocity.x < 0.f) THEN (rightLeft = -1.f) ELSE (rightLeft = 1.f;)
      velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
      texture = run;
  }
  else texture = idle;
  // reset Velocity
  velocity = {};

  // DRAW THE CHARACTER
  // source is a section in the sprite sheet (dictates which part of the texture to use/draw)
  Rectangle source{frame * width, 0.f, rightLeft * width, height};// ((pos.x),(pos.y),(width),(height))
  // dest is a destination rectangle containing information where to draw this rectangle int the
  // sprite sheet as well as how big to draw it(location in the map)
  Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};// ((pos.x),(pos.y),(width),(height))
  // origin is a Vector that designates the origin of the texture
  Vector2 origin{};// ((pos.x),(pos.y))
  // rotation is the... rotation
  float rotation{0.f};
  // draw the character-----------------------------------------
  DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
}
