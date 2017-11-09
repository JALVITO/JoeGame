//
//  Entity.cpp
//  JoeGame
//
//  Created by Juan Lizarraga on 11/4/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include "Entity.h"

Entity::Entity(){};

Entity::Entity(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp) : Object(_density, _type, _size, _position, texture){
    
    maxHp = _maxHp;
    hp = maxHp;
    isGrounded = false;
    
}

void Entity::die(){
    cout << "endl" << endl;
    Destroy();
}

void Entity::update(vector<Object> &colliders){
    Object::update(colliders);
    
    if(hp <= 0)
        die();
}

bool Entity::isItGrounded(){
    return isGrounded;
}

void Entity::recieveDamage(int _damage){
    hp -= _damage;
    cout << hp << endl;
}

