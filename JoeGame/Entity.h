//
//  Entity.h
//  JoeGame
//
//  Created by Juan Lizarraga on 11/4/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Entity_h
#define Entity_h

#include "Object.h"

class Entity : public Object{
protected:
    int hp, maxHp;
    Vector2f selfVelocity;
public:
    Entity();
    Entity(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp);
    void die();
    void update(vector<Object> &colliders);
    bool isItGrounded();
    void recieveDamage(int _damage);
    void setSelfVelocity(Vector2f _selfVelocity);
    void underlap(Rect<float> &otherBounds, int axis);
    bool collidesWith(Object &other, int axis);
    Vector2f getSelfVelocity();
};

#endif /* Entity_h */
