//
//  Weapon.h
//  JoeGame
//
//  Created by Adrian Mancilla on 11/7/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Weapon_h
#define Weapon_h

#include "Object.h"

class Bullet;


class Weapon : public Object{
protected:
    double firingRate, firingForce, timeUntilNextFire;
    Texture bulletTexture;
    bool isPlayer, canFire;
    vector<int> bulletType;
    float bulletMass, bulletDamage;
    Vector2f bulletSize;
public:
    Weapon();
    Weapon(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, double _firingRate, double _firingForce, Texture* _bulletTexture, bool _isPlayer, vector<int>& _bulletType, float _bulletMass, float _bulletDamage, Vector2f _bulletSize);
    void fire(vector<Bullet> &bullets);
    void update();
};

#endif /* Weapon_h */
