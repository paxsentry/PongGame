#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Bat
{
public:
   Bat(float startX, float startY);
   FloatRect getPosition();
   RectangleShape getShape();
   void moveLeft();
   void moveRight();
   void update();

private:
   Vector2f position;
   RectangleShape batShape;
   float batSpeed = 29.9f;
};