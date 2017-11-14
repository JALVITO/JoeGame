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
#include "GUI_Object.h"
#include "GUI_Text.h"
#include "GUI_Button.h"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(900, 600), "SFML window", sf::Style::Close);
    
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(0);
    window.setVerticalSyncEnabled(true);
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    
    // Load a sprite to display

    sf::Texture playerTexture, blockTexture, attractorTexture, repellerTexture, gunTexture, bulletTexture, guiTexture, buttonTexture;
    
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
    
    if (!attractorTexture.loadFromFile(resourcePath() + "attractor.png")) {
        return EXIT_FAILURE;
    }
    
    if (!repellerTexture.loadFromFile(resourcePath() + "repeller.png")) {
        return EXIT_FAILURE;
    }
    if (!guiTexture.loadFromFile(resourcePath() + "gui.png")) {
        return EXIT_FAILURE;
    }
    if (!buttonTexture.loadFromFile(resourcePath() + "2.png")) {
        return EXIT_FAILURE;
    }
    
    
    int MOUSE_INPUTS[3] = {0, 0, 0}; // LEFT, MIDDLE, RIGHT
    int KEY_INPUTS[5] = {0, 0, 0, 0, 0}; // W, A, S, D, SPACEBAR
    
    Player* player;
    vector<Object> allObjects;
    vector<Enemy> allEnemies;
    vector<Bullet> allBullets;
    vector<Magnet> allMagnets;
    vector<Loot> allLoots;
    
    
    
    vector<int> type = {1, 1, 1, 1};
    vector<int> type_NG = {0, 1, 1, 1};
    vector<int> type_NM = {1, 0, 1, 1};
    vector<int> type_NG_NM = {0, 0, 1, 1};
    
    allLoots.push_back(Loot(0.05, type, Vector2f(12, 12), Vector2f(350, 350), &gunTexture, 0, 3));
    
    Weapon weapon = Weapon(1, type_NG_NM, Vector2f(32,24), Vector2f(200,450), &gunTexture, 8, 3, &bulletTexture, true, type_NG, 0.15, 2, Vector2f(16, 16));
    
    Magnet lootMagnet = Magnet(1, type_NG, Vector2f(32, 32), Vector2f(), &attractorTexture, 50, -30);
    
    player = new Player(0.75, type, Vector2f(50, 50), Vector2f(150, 500), &playerTexture, 100, 10, 5, &weapon, &lootMagnet);

    allObjects.push_back(Object(5, type_NG_NM, Vector2f(1000, 64), Vector2f(-100, 555), &blockTexture));
    allObjects.push_back(Object(5, type_NG_NM, Vector2f(1000, 64), Vector2f(-100, 150), &blockTexture));
    allObjects.push_back(Object(5, type_NG_NM, Vector2f(64, 800), Vector2f(500, 0), &blockTexture));
    allObjects.push_back(Object(5, type_NG_NM, Vector2f(64, 800), Vector2f(50, 0), &blockTexture));
    
    //allEnemies.push_back(Enemy(0.1, type, Vector2f(32,64), Vector2f(200,225), &playerTexture, 100, &weapon));
    
    //allMagnets.push_back((Magnet(1, type_NG, Vector2f(64, 64), Vector2f(250, 250), &repellerTexture, 50, 800)));
    
    //allMagnets.push_back((Magnet(1, type_NG, Vector2f(32, 32), Vector2f(350, 355), &attractorTexture, 50, -800)));
    
    GUI_Object guiobj = GUI_Object(Vector2f(16,16), Vector2f(200,200), &guiTexture);
    
    Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    GUI_Text guitext = GUI_Text(Vector2f(0,0), "hola", 30, &font, Color::Red);
    GUI_Button guibutton = GUI_Button(Vector2f(16,16), Vector2f(100,100), &buttonTexture, guitext, &guiTexture);
    
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
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
                KEY_INPUTS[1] = 1;
                //allPlayers.at(0).setSelfVelocity(Vector2f(-fuck_copy_paste, 0));
            }
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
                KEY_INPUTS[3] = 1;
                //allPlayers.at(0).setSelfVelocity(Vector2f(fuck_copy_paste, 0));
            }
            
            if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Space)) {
                if(player->isItGrounded())
                    player->addForce(Vector2f(0, -player->getJumpForce()));
            }
            
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A) {
                KEY_INPUTS[1] = 0;
                //allPlayers.at(0).setSelfVelocity(Vector2f(0, allPlayers.at(0).getSelfVelocity().y));
            }
            
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D) {
                KEY_INPUTS[3] = 0;
                //allPlayers.at(0).setSelfVelocity(Vector2f(0, allPlayers.at(0).getSelfVelocity().y));
            }
            
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
                MOUSE_INPUTS[0] = 1;
                //allPlayers.at(0).fireWeapon(allBullets);
            }
            
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left) {
                MOUSE_INPUTS[0] = 0;
                //allPlayers.at(0).fireWeapon(allBullets);
            }
            
            //Magnet debugging
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N) {
                Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                mousePos -= Vector2f(16,16);
                allMagnets.push_back((Magnet(1, type_NG, Vector2f(32, 32), mousePos, &attractorTexture, 50, -800)));
            }
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
                Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                mousePos -= Vector2f(16,16);
                allMagnets.push_back((Magnet(1, type_NG, Vector2f(32, 32), mousePos, &repellerTexture, 50, 800)));
            }
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B) {
                allMagnets.clear();
            }
        }
        
        if(MOUSE_INPUTS[0])
            player->fireWeapon(allBullets);
        
        if(KEY_INPUTS[3])
            player->setSelfVelocity(Vector2f(player->getMoveForce(), player->getSelfVelocity().y));
        
        if(KEY_INPUTS[1])
           player->setSelfVelocity(Vector2f(-player->getMoveForce(), player->getSelfVelocity().y));
        
        if(!KEY_INPUTS[1] && !KEY_INPUTS[3])
            player->setSelfVelocity(Vector2f(0, player->getSelfVelocity().y));
        
        // Update Magnet physics
        for(int i = 0; i < allMagnets.size(); i++){
            if (allMagnets.at(i).isItDestroyed()){
                allMagnets.erase(allMagnets.begin() + i);
                continue;
            }
            allMagnets.at(i).update(allObjects, allBullets, player, allEnemies);
        }
        
        // Update Bullet physicss
        for(int i = 0; i < allBullets.size(); i++){
            if (allBullets.at(i).isItDestroyed()){
                allBullets.erase(allBullets.begin() + i);
                continue;
            }
            allBullets.at(i).update(allObjects, player, allEnemies, allMagnets);
        }
        
        // Update Player physics
        player->update(allObjects, allMagnets, allLoots);
        
        
        // Update Loot Physics
        for(int i = 0; i < allLoots.size(); i++){
            if (allLoots.at(i).isItDestroyed()){
                allLoots.erase(allLoots.begin() + i);
                continue;
            }
            allLoots.at(i).update(allObjects, player);
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
        player->draw(&window);
        
        
        // Draw Enemies
        for(int i = 0; i < allEnemies.size(); i++){
            allEnemies.at(i).draw(&window);
        }
        
        // Draw Bullets
        for(int i = 0; i < allBullets.size(); i++){
            allBullets.at(i).draw(&window);
        }
        
        // Draw Loot
        for(int i = 0; i < allLoots.size(); i++){
            allLoots.at(i).draw(&window);
        }
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
