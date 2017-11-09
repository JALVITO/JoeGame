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

class Weapon : public Object{
protected:
    double firingRate;
public:
    Weapon();
    Weapon(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, double _firingRate);
    void fire();
};

#endif /* Weapon_h */
