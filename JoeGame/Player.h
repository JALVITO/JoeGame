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

class Bullet;

class Player : public Entity{
protected:
    float jumpForce, moveForce;
    Weapon weapon;
    RectangleShape rayCast;
    //Inventory inventory (tbi)
    //Magnet magnet (tbi)
    
public:
    Player();
    Player(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, float _jumpForce, float _moveForce, Weapon* _weapon);
    void update(vector<Object> &colliders);
    void draw(RenderWindow* window);
    void pointWeapon(RenderWindow* window);
    void fireWeapon(vector<Bullet> &bullets);
    Weapon* getWeapon();
    
};


#endif /* Player_h */
