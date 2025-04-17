#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameMap.h"
#include "Pac.h"
#include <iostream>
#include <cmath>
using namespace std;
using namespace sf;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    window.setFramerateLimit(60);  
    GameMap Gm;
    Pac pacman1;
    const int tileSize = 50;
    const int pointSize = 10;
    const int pacSize = 30;
    const float moveSpeed = 200.0f;  

    sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
    CircleShape point(pointSize / 2);
    CircleShape pac(pacSize / 2);

  
    int gridX = 0, gridY = 0;
    for (int i = 0; i < Gm.map1.size(); i++) {
        for (int j = 0; j < Gm.map1[i].size(); j++) {
            if (Gm.map1[i][j] == 'P') {
                gridX = i;
                gridY = j;
                break;
            }
        }
    }

   
    float visualX = gridY * tileSize + (tileSize - pacSize) / 2;
    float visualY = gridX * tileSize + (tileSize - pacSize) / 2;
 
    float targetX = visualX;
    float targetY = visualY;

    Vector2i direction(0, 0);
    Vector2i nextDirection(0, 0);
    bool isMoving = false;

    Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        float deltaTime = clock.restart().asSeconds();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        if (Keyboard::isKeyPressed(Keyboard::W)) nextDirection = { -1, 0 };
        else if (Keyboard::isKeyPressed(Keyboard::S)) nextDirection = { 1, 0 };
        else if (Keyboard::isKeyPressed(Keyboard::A)) nextDirection = { 0, -1 };
        else if (Keyboard::isKeyPressed(Keyboard::D)) nextDirection = { 0, 1 };

        
        if (!isMoving) {
            
            int newX = gridX + nextDirection.x;
            int newY = gridY + nextDirection.y;

            
            if (newX >= 0 && newY >= 0 && newX < Gm.map1.size() && newY < Gm.map1[0].size() &&
                Gm.map1[newX][newY] != '#') {
                direction = nextDirection;

               
                Gm.map1[gridX][gridY] = ' ';
                gridX = newX;
                gridY = newY;
                Gm.map1[gridX][gridY] = 'P';

                
                targetX = gridY * tileSize + (tileSize - pacSize) / 2;
                targetY = gridX * tileSize + (tileSize - pacSize) / 2;
                isMoving = true;
            }
         
            else if (direction.x != 0 || direction.y != 0) {
                newX = gridX + direction.x;
                newY = gridY + direction.y;

                if (newX >= 0 && newY >= 0 && newX < Gm.map1.size() && newY < Gm.map1[0].size() &&
                    Gm.map1[newX][newY] != '#') {
                 
                    Gm.map1[gridX][gridY] = ' ';
                    gridX = newX;
                    gridY = newY;
                    Gm.map1[gridX][gridY] = 'P';

                     
                    targetX = gridY * tileSize + (tileSize - pacSize) / 2;
                    targetY = gridX * tileSize + (tileSize - pacSize) / 2;
                    isMoving = true;
                }
            }
        }

    
        if (isMoving) {
            float dx = targetX - visualX;
            float dy = targetY - visualY;
            float distance = sqrt(dx * dx + dy * dy);

            if (distance < 2.0f) {
             
                visualX = targetX;
                visualY = targetY;
                isMoving = false;
            }
            else {
                
                float moveAmount = moveSpeed * deltaTime;
                if (moveAmount > distance) moveAmount = distance;

                float ratio = moveAmount / distance;
                visualX += dx * ratio;
                visualY += dy * ratio;
            }
        }

        window.clear();

        for (int i = 0; i < Gm.map1.size(); i++) {
            for (int j = 0; j < Gm.map1[i].size(); j++) {
                if (Gm.map1[i][j] == '#') {
                    tile.setFillColor(sf::Color::Blue);
                    tile.setPosition(j * tileSize, i * tileSize);
                    window.draw(tile);
                }
                else if (Gm.map1[i][j] == '.') {
                    point.setFillColor(sf::Color::Yellow);
                    point.setPosition(j * tileSize + (tileSize - pointSize) / 2,
                        i * tileSize + (tileSize - pointSize) / 2);
                    window.draw(point);
                }
                else if (Gm.map1[i][j] == 'P') {
                }
                else {
                    tile.setFillColor(sf::Color::Black);
                    tile.setPosition(j * tileSize, i * tileSize);
                    window.draw(tile);
                }
            }
        }

        pac.setFillColor(sf::Color::Yellow);
        pac.setPosition(visualX, visualY);
        window.draw(pac);

        window.display();
    }

    return 0;
}