//
//  Bullet.h
//  JoeGame
//
//  Created by Adrian Mancilla on 11/8/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Bullet_h
#define Bullet_h

#include "Object.h"

class Bullet : public Object{
protected:
    double damage;
public:
    Bullet();
    Bullet(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, double _damage);
    void update(vector<Object> &colliders);
    void DealDamage();
    void Destroy();
    bool collidesWith(Object &other);
};

#endif /* Bullet_h */
