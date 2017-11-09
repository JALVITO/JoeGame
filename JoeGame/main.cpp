#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "Entity.h"
#include "Weapon.h"
#include "Player.h"
#include "Bullet.h"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(900, 600), "SFML window", sf::Style::Close);
    
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(0);

    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    
    // Load a sprite to display
    sf::Texture playerTexture, blockTexture, gunTexture;
    if (!playerTexture.loadFromFile(resourcePath() + "pacman.png")) {
        return EXIT_FAILURE;
    }
    
    if (!gunTexture.loadFromFile(resourcePath() + "gun.png")) {
        return EXIT_FAILURE;
    }
    
    if (!blockTexture.loadFromFile(resourcePath() + "block.png")) {
        return EXIT_FAILURE;
    }
    
    vector<Object> allObjects;
    vector<Player> allPlayers;
    vector<Bullet> allBullets;

    vector<int> type = {0, 1, 1, 1};
    
    Weapon weapon = Weapon(1, type, Vector2f(32,24), Vector2f(200,450), &gunTexture, 20);
    
    allObjects.push_back(Object(1, type, Vector2f(1000, 64), Vector2f(-100, 550), &blockTexture));
    allObjects.push_back(Object(1, type, Vector2f(1000, 64), Vector2f(-100, 150), &blockTexture));
    allObjects.push_back(Object(1, type, Vector2f(64, 800), Vector2f(500, 0), &blockTexture));
    allObjects.push_back(Object(1, type, Vector2f(64, 800), Vector2f(50, 0), &blockTexture));
    allObjects.push_back(Object(1, type, Vector2f(48, 48), Vector2f(200, 435), &blockTexture));
    allPlayers.push_back(Player(1, type, Vector2f(32, 64), Vector2f(200, 275), &playerTexture, 100, 0, 0, &weapon));
    allBullets.push_back(Bullet(1, type, Vector2f(8,8), Vector2f(300,300), &playerTexture, 5));
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            float fuck_copy_paste = 0.8;
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
                allPlayers.at(0).addForce(Vector2f(-fuck_copy_paste, 0));
            }
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
                allPlayers.at(0).addForce(Vector2f(fuck_copy_paste, 0));
            }
            
            if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Space)) {
                if(allPlayers.at(0).isItGrounded())
                    allPlayers.at(0).addForce(Vector2f(0, -fuck_copy_paste * 2.5));
            }
            
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A) {
                allPlayers.at(0).addForce(Vector2f(fuck_copy_paste, 0));
            }
            
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D) {
                allPlayers.at(0).addForce(Vector2f(-fuck_copy_paste, 0));
            }
        }

        // Update Bullet physics
        for(int i = 0; i < allBullets.size(); i++){
            if (allBullets.at(i).isItDestroyed()){
                allBullets.erase(allBullets.begin() + i);
                continue;
            }
            allBullets.at(i).update(allObjects,allPlayers);
        }
        
        // Update Player physics
        for(int i = 0; i < allPlayers.size(); i++){
            allPlayers.at(i).update(allObjects);
        }
        
        // Update Object physics
        for(int i = 0; i < allObjects.size(); i++){
            allObjects.at(i).update();
        }

        // Clear screen
        window.clear(sf::Color::White);

        // Draw all objects
        for(int i = 0; i < allObjects.size(); i++){
            allObjects.at(i).draw(&window);
        }
        
        // Draw Players
        for(int i = 0; i < allPlayers.size(); i++){
            allPlayers.at(i).draw(&window);
        }
        
        // Draw Bullets
        for(int i = 0; i < allBullets.size(); i++){
            allBullets.at(i).draw(&window);
        }
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
