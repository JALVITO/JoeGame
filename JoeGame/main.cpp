#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "Entity.h"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML window", sf::Style::Close);
    
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(0);

    /*/
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    /*/
    
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "block.png")) {
        return EXIT_FAILURE;
    }
    
    vector<Object> allObjects;
    
    vector<int> type = {1, 1, 1, 1};
    Entity player = Entity(0.001, type, Vector2f(32, 64), Vector2f(200, 450), &texture, 100);
    
    type = {0, 1, 1, 1};
    allObjects.push_back(Object(0.001, type, Vector2f(1000, 128), Vector2f(-100, 550), &texture));
    allObjects.push_back(Object(0.001, type, Vector2f(1000, 128), Vector2f(-100, 250), &texture));
    allObjects.push_back(Object(0.001, type, Vector2f(128, 1000), Vector2f(900, 0), &texture));
    allObjects.push_back(Object(0.001, type, Vector2f(128, 1000), Vector2f(50, 0), &texture));
                         
    /*/
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::Black);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }
    
    // Play the music
    music.play();
    /*/
    
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
            float fuck_copy_paste = 0.08;
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                player.addForce(Vector2f(-fuck_copy_paste, 0));
            }
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                player.addForce(Vector2f(fuck_copy_paste, 0));
            }
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                if(player.isItGrounded())
                    player.addForce(Vector2f(0, -fuck_copy_paste));
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
        vector<Object> empty = {};
        for(int i = 0; i < allObjects.size(); i++){
            allObjects.at(i).update(empty);
        }
        
        // Clear screen
        window.clear();

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
