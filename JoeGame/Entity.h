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
public:
    Entity();
    Entity(double _density, vector<int> &_type, Vector2f _size, Texture* texture, int _maxHp);
    Entity(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp);
    void die();
    void update(vector<Object> &colliders);
    bool isItGrounded();
};

#endif /* Entity_h */
