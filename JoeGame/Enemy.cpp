//
//  Enemy.cpp
//  JoeGame
//
//  Created by Adrian Mancilla on 11/7/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include "Enemy.h"
#include "Weapon.h"

Enemy::Enemy(){};

Enemy::Enemy(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, Weapon _weapon) : Entity(_density, _type, _size, _position, texture, _maxHp){
    weapon = _weapon;
};
