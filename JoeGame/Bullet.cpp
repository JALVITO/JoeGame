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

Bullet::Bullet(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, double _damage) : Object(_density, _type, _size, _position, texture){
    damage = _damage;
}

void Bullet::update(vector<Object> &colliders){
    // Add gravity force
    addForce(Vector2f(0, GRAVITY * mass), 0);
    // Add acceleration to velocity
    velocity += acceleration;
    // Reset acceleration
    acceleration = Vector2f();
    // Add velocity to position on the x axis
    position += velocity;
    sprite.setPosition(position);
    for(int i = 0; i < colliders.size(); i++){
        if(collidesWith(colliders.at(i))){
            try{
                DealDamage(colliders.at(i));
                Destroy();
            }catch(exception e){
                Destroy();
            }
           
        }
    }
}

void Bullet::Destroy(){

}

void Bullet::DealDamage(Object &other){
    
}

bool Bullet::collidesWith(Object &other){
    //punto = bullet.position
    Rect<float> otherBounds = other.getSprite()->getGlobalBounds();
    
    if(getPosition().x > otherBounds.left && getPosition().x < otherBounds.left + otherBounds.width && getPosition().y > otherBounds.top && getPosition().y < otherBounds.top + otherBounds.height){
        return true;
    }
    
    return false;
}


