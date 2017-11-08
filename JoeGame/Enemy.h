//
//  Enemy.h
//  JoeGame
//
//  Created by Adrian Mancilla on 11/7/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Enemy_h
#define Enemy_h

#include "Entity.h"
#include "Weapon.h"


class Enemy : public Entity{
protected:
    Weapon weapon;
public:
    Enemy();
    Enemy(double _density, vector<int> &_type, Vector2f _size, Texture* texture, int _maxHp, Weapon _weapon);
    Enemy(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, Weapon _weapon);
    void pathFinding();
    
};
#endif /* Enemy_h */
