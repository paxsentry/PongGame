#include "stdafx.h"
#include "Ball.h"
#include "Bat.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

// Avoid having to put sf in front of all the SFML classes and functions
using namespace sf;

// Game start
int main()
{
   int windowWidth = 1024;
   int windowHeight = 768;

   // Make a window that is 1024 by 768 pixels
   // And has the title "Pong"
   RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");

   int score = 0;
   int lives = 3;

   // Create bat
   Bat bat(windowWidth / 2, windowHeight - 20);

   // Create ball
   Ball ball(windowWidth / 2, 1);

   // Create HUD - Create a "Text" object called "message"
   Text hud;

   Font font;
   font.loadFromFile("DS-DIGIT.ttf");

   hud.setFont(font);
   hud.setCharacterSize(75);
   hud.setFillColor(sf::Color::White);

   while (window.isOpen())
   {
      //
      // Handle player input
      //
      Event event;
      while (window.pollEvent(event))
      {
         if (event.type == Event::Closed) {
            window.close();
         }

         if (Keyboard::isKeyPressed(Keyboard::Left)) {
            // Move left
            bat.moveLeft();
         }
         else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            // Move right
            bat.moveRight();
         }
         else if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
         {
            // Quit
            window.close();
         }
      }

      //
      // Update the frame
      //

      // Ball hitting the bottom
      if (ball.getPosition().top > windowHeight) {
         // Reverse the ball direction
         ball.hitBottom();

         // Remove life
         lives--;

         // Check zero lives
         if (lives < 1) {
            score = 0; // reset score
            lives = 3; // reset lives
         }
      }

      // Ball hitting top
      if (ball.getPosition().top < 0) {
         ball.reboundBatOrTop();

         // Increase score
         score++;
      }

      // Ball hitting sides
      if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth) {
         ball.reboundSides();
      }

      // Has the ball hit the bat?
      if (ball.getPosition().intersects(bat.getPosition())) {
         
         // Hit detected, reverse ball, add score
         ball.reboundBatOrTop();
         score++;
      }

      ball.update();
      bat.update();

      // Update the HUD text
      std::stringstream ss;
      ss << "Score: " << score << "   Lives: " << lives;
      hud.setString(ss.str());

      //
      // Draw the frame
      //

      window.clear(Color(26, 128, 182, 255));

      window.draw(bat.getShape());
      window.draw(ball.getShape());

      window.draw(hud);

      // Show the drawings
      window.display();
   }

   return 0;
}