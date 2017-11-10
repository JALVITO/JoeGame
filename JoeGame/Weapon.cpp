//
//  Weapon.cpp
//  JoeGame
//
//  Created by Adrian Mancilla on 11/7/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include "Weapon.h"
#include "Bullet.h"

Weapon::Weapon(){};

Weapon::Weapon(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, double _firingRate, double _firingForce, Texture* _bulletTexture, bool _isPlayer) : Object(_density, _type, _size, _position, texture){
    firingRate = _firingRate;
    firingForce = _firingForce;
    bulletTexture = *_bulletTexture;
    isPlayer = _isPlayer;
}

void Weapon::fire(vector<Bullet> &bullets){
    vector<int> type_NO_GRAV = {0, 1, 1, 1};
    Bullet newBullet = Bullet(5, type_NO_GRAV, Vector2f(8, 8), Vector2f(position.x, position.y), &bulletTexture, 10, isPlayer);
    Vector2f force = Vector2f(firingForce * cos(sprite.getRotation() * M_PI / 180), firingForce * sin(sprite.getRotation() * M_PI / 180));
    newBullet.addForce(force);
    bullets.push_back(newBullet);
}
