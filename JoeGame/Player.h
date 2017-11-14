//
//  Player.h
//  JoeGame
//
//  Created by Juan Lizarraga on 11/8/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include "Entity.h"
#include "Weapon.h"
#include "Magnet.h"

class Bullet;

class Player : public Entity{
protected:
    float jumpForce, moveForce;
    Weapon weapon;
    RectangleShape rayCast;
    Magnet lootMagnet;
    int gold, gems;
    //Inventory inventory (tbi)
    
    
public:
    Player();
    Player(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, float _jumpForce, float _moveForce, Weapon* _weapon, Magnet* lootMagnet);
    void update(vector<Object> &objectCol, vector<Magnet> &magnetCol, vector<Loot> &lootCol);
    void draw(RenderWindow* window);
    void pointWeapon(RenderWindow* window);
    void fireWeapon(vector<Bullet> &bullets);
    float getJumpForce();
    float getMoveForce();
    Weapon* getWeapon();
    void getLoot(int lootType, int lootAmount);
    
};


#endif /* Player_h */
