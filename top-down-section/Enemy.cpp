#include "Enemy.h"
#include "raymath.h"


Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
  worldPos = pos;
  texture = idle_texture;
  idle = idle_texture;
  run = run_texture;
  width = texture.width/maxFrame;
  height = texture.height;
  speed = 3.f;
}

void Enemy::tick(float deltaTime)
{
  if (!getAlive()) return;

  velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());

  // distance of the radius bevor he stopps after reaching the knight
  if (Vector2Length(velocity) < radius) velocity = {};


  BaseCharacter::tick(deltaTime);

  if (CheckCollisionRecs(target->GetCollisionRec(), GetCollisionRec()))
  {
    target->takeDamage(damagePerSec * deltaTime);
  }

}


Vector2 Enemy::getScreenPos()
{
  // subtract the enemys worldPos from the Knights worldPos
  return Vector2Subtract(worldPos, target->getWorldPos());
}
