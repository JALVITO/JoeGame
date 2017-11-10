#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "Entity.h"
#include "Weapon.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Magnet.h"

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
    sf::Texture playerTexture, blockTexture, magnetTexture, gunTexture, bulletTexture;
    if (!playerTexture.loadFromFile(resourcePath() + "pacman.png")) {
        return EXIT_FAILURE;
    }
    
    if (!gunTexture.loadFromFile(resourcePath() + "gun.png")) {
        return EXIT_FAILURE;
    }
    
    if (!bulletTexture.loadFromFile(resourcePath() + "bullet.png")) {
        return EXIT_FAILURE;
    }
    
    if (!blockTexture.loadFromFile(resourcePath() + "block.png")) {
        return EXIT_FAILURE;
    }
    
    if (!magnetTexture.loadFromFile(resourcePath() + "magnet.png")) {
        return EXIT_FAILURE;
    }
    
    vector<Object> allObjects;
    vector<Player> allPlayers;
    vector<Enemy> allEnemies;
    vector<Bullet> allBullets;
    vector<Magnet> allMagnets;
    
    vector<int> type = {1, 1, 1, 1};
    vector<int> type_NG = {0, 1, 1, 1};
    vector<int> type_NM = {1, 0, 1, 1};
    vector<int> type_NG_NM = {0, 0, 1, 1};
    
    Weapon weapon = Weapon(1, type_NG_NM, Vector2f(32,24), Vector2f(200,450), &gunTexture, 20, 0.3, &bulletTexture, true);

    allObjects.push_back(Object(5, type_NG_NM, Vector2f(1000, 64), Vector2f(-100, 550), &blockTexture));
    allObjects.push_back(Object(5, type_NG_NM, Vector2f(1000, 64), Vector2f(-100, 150), &blockTexture));
    allObjects.push_back(Object(5, type_NG_NM, Vector2f(64, 800), Vector2f(500, 0), &blockTexture));
    allObjects.push_back(Object(5, type_NG_NM, Vector2f(64, 800), Vector2f(50, 0), &blockTexture));
    allPlayers.push_back(Player(1, type_NG, Vector2f(32, 64), Vector2f(150, 275), &playerTexture, 100, 0, 0, &weapon));
    
    allEnemies.push_back(Enemy(1, type_NG, Vector2f(32,64), Vector2f(200,225), &playerTexture, 100, &weapon));
    
    allMagnets.push_back((Magnet(1, type_NG, Vector2f(50, 50), Vector2f(300, 350), &magnetTexture, 50, 0.3)));
    
    //allMagnets.push_back((Magnet(1, type_NG, Vector2f(50, 50), Vector2f(300, 450), &magnetTexture, 50, 0.3)));
    
    
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
            
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
                allPlayers.at(0).fireWeapon(allBullets);
            }
        }

        
        // Update Magnet physics
        for(int i = 0; i < allMagnets.size(); i++){
            allMagnets.at(i).update(allObjects, allBullets, allPlayers, allEnemies);
        }
        
        // Update Bullet physicss
        for(int i = 0; i < allBullets.size(); i++){
            if (allBullets.at(i).isItDestroyed()){
                allBullets.erase(allBullets.begin() + i);
                continue;
            }
            allBullets.at(i).update(allObjects, allPlayers, allEnemies);
        }
        
        // Update Player physics
        for(int i = 0; i < allPlayers.size(); i++){
            allPlayers.at(i).update(allObjects);
        }
        
        // Update Enemy physics
        for(int i = 0; i < allEnemies.size(); i++){
            if (allEnemies.at(i).isItDestroyed()){
                allEnemies.erase(allEnemies.begin() + i);
                continue;
            }
            /*/
            if(allEnemies.at(i).isItGrounded()){
                allEnemies.at(i).addForce(Vector2f(0, -1.5));
            }
            /*/
            allEnemies.at(i).update(allObjects);
        }
        
        // Update Object physics
        for(int i = 0; i < allObjects.size(); i++){
            allObjects.at(i).update();
        }

        // Clear screen
        window.clear(sf::Color::White);

        
        // Draw Magnets
        for(int i = 0; i < allMagnets.size(); i++){
            allMagnets.at(i).draw(&window);
        }
        
        // Draw all objects
        for(int i = 0; i < allObjects.size(); i++){
            allObjects.at(i).draw(&window);
        }
        
        // Draw Players
        for(int i = 0; i < allPlayers.size(); i++){
            allPlayers.at(i).draw(&window);
        }
        
        // Draw Enemies
        for(int i = 0; i < allEnemies.size(); i++){
            allEnemies.at(i).draw(&window);
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
