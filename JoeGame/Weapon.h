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
    double firingRate, firingForce;
    Texture bulletTexture;
    bool isPlayer;
public:
    Weapon();
    Weapon(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, double _firingRate, double _firingForce, Texture* _bulletTexture, bool _isPlayer);
    void fire(vector<Bullet> &bullets);
};

#endif /* Weapon_h */
