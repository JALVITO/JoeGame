#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "Entity.h"

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
    sf::Texture playerTexture, texture;
    if (!playerTexture.loadFromFile(resourcePath() + "pacman.png")) {
        return EXIT_FAILURE;
    }
    
    if (!texture.loadFromFile(resourcePath() + "block.png")) {
        return EXIT_FAILURE;
    }
    
    vector<Object> allObjects;
    
    vector<int> type = {1, 1, 1, 1};
    Entity player = Entity(1, type, Vector2f(32, 64), Vector2f(200, 450), &playerTexture, 100);
    type = {0, 1, 1, 1};
    
    allObjects.push_back(Object(1, type, Vector2f(1000, 64), Vector2f(-100, 550), &texture));
    allObjects.push_back(Object(1, type, Vector2f(1000, 64), Vector2f(-100, 150), &texture));
    allObjects.push_back(Object(1, type, Vector2f(64, 800), Vector2f(500, 0), &texture));
    allObjects.push_back(Object(1, type, Vector2f(64, 800), Vector2f(50, 0), &texture));
    
    allObjects.push_back(Object(1, type, Vector2f(48, 48), Vector2f(200, 435), &texture));
    
    //allObjects.at(4).setVelocity(Vector2f(0, -2));
    //allObjects.at(1).setVelocity(Vector2f(0, 2));
    //allObjects.at(3).setVelocity(Vector2f(2, 0));
    
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
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                player.addForce(Vector2f(-fuck_copy_paste, 0));
            }
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                player.addForce(Vector2f(fuck_copy_paste, 0));
            }
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                if(player.isItGrounded())
                    player.addForce(Vector2f(0, -fuck_copy_paste * 2.5));
            }
            
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left) {
                player.addForce(Vector2f(fuck_copy_paste, 0));
            }
            
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right) {
                player.addForce(Vector2f(-fuck_copy_paste, 0));
            }
        }
        
        // Update player physics
        player.update(allObjects);
        
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
        
        // Draw Player
        player.draw(&window);
    
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
