//
//  Bullet.cpp
//  JoeGame
//
//  Created by Adrian Mancilla on 11/8/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include <typeinfo>

#include "Bullet.h"

Bullet::Bullet(){};

Bullet::Bullet(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _damage) : Object(_density, _type, _size, _position, texture){
    damage = _damage;
    isDestroyed = false;
}

void Bullet::update(vector<Object> &objectcol, vector<Entity> &entitycol){
    // Add gravity force
    addForce(Vector2f(0, GRAVITY * mass), 0);
    // Add acceleration to velocity
    velocity += acceleration;
    // Reset acceleration
    acceleration = Vector2f();
    // Add velocity to position on the x axis
    position += velocity;
    sprite.setPosition(position);
    for(int i = 0; i < objectcol.size(); i++){
        if(collidesWith(objectcol.at(i))){
            Destroy();
        }
    }

    for(int i = 0; i < entitycol.size(); i++){
        if(collidesWith(entitycol.at(i))){
            DealDamage(entitycol.at(i), damage);
            Destroy();
        }
    }
}


void Bullet::DealDamage(Entity &other, int _damage){
    other.recieveDamage(_damage);
}

bool Bullet::collidesWith(Object &other){
    center = Vector2f(getPosition().x + getSize().x / 2.0 , getPosition().y + getSize().y / 2.0);
    Rect<float> otherBounds = other.getSprite()->getGlobalBounds();
    
    if(center.x > otherBounds.left && center.x < otherBounds.left + otherBounds.width && center.y > otherBounds.top && center.y < otherBounds.top + otherBounds.height){
        return true;
    }
    
    return false;
}

