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

Weapon::Weapon(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, double _firingRate, double _firingForce, Texture* _bulletTexture, bool _isPlayer, vector<int>& _bulletType, float _bulletMass, float _bulletDamage, Vector2f _bulletSize) : Object(_mass, _type, _size, _position, texture){
    firingRate = _firingRate;
    firingForce = _firingForce;
    bulletTexture = *_bulletTexture;
    isPlayer = _isPlayer;
    bulletType = _bulletType;
    bulletMass = _bulletMass;
    bulletDamage = _bulletDamage;
    bulletSize = _bulletSize;
    canFire = true;
}

void Weapon::fire(vector<Bullet> &bullets){
    if(!canFire)
        return;
    Bullet newBullet = Bullet(bulletMass, bulletType, bulletSize, Vector2f(position.x, position.y), &bulletTexture, bulletDamage, isPlayer);
    Vector2f force = Vector2f(firingForce * cos(sprite.getRotation() * M_PI / 180), firingForce * sin(sprite.getRotation() * M_PI / 180));
    newBullet.addForce(force);
    bullets.push_back(newBullet);
    canFire = false;
}

void Weapon::update(){
    sprite.setPosition(position);
    if(!canFire){
        timeUntilNextFire -= 1;
        if(timeUntilNextFire <= 0){
            timeUntilNextFire = 60 / firingRate;
            canFire = true;
        }
    }
}
