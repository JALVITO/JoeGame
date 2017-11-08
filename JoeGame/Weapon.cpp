//
//  Weapon.cpp
//  JoeGame
//
//  Created by Adrian Mancilla on 11/7/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include "Weapon.h"

Weapon::Weapon(){};

Weapon::Weapon(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, double _firingRate, double _damage) : Object(_density, _type, _size, _position, texture){
    firingRate = _firingRate;
    damage = _damage;
}
