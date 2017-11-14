//
//  Loot.cpp
//  JoeGame
//
//  Created by Guilherme Bittencourt de Borba on 11/13/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include "Loot.h"
#include "Player.h"

Loot::Loot(){};

Loot::Loot(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _lootType, int _lootAmount) : Object(_mass, _type, _size, _position, texture){
    lootType = _lootType;
    lootAmount = _lootAmount;
}


void Loot::update(vector<Object> &colliders, Player* playerCol){
    // Add gravity force
    addForce(Vector2f(0, GRAVITY * mass), 0);
    // Add acceleration to velocity
    velocity += acceleration;
    // Reset acceleration
    acceleration = Vector2f();
    // Add velocity to position on the x axis
    position.x += velocity.x;
    sprite.setPosition(position);
    // Check for collision with each of the provided objects
    for(int i = 0; i < colliders.size(); i++){
        Object::collidesWith(colliders.at(i), 0);
    }
    // Add velocity to position on the y axis
    position.y += velocity.y;
    sprite.setPosition(position);
    // Check for collision with each of the provided objects
    for(int i = 0; i < colliders.size(); i++){
        Object::collidesWith(colliders.at(i), 1);
    }
    
    // Check for collision with player
    if(collidesWith(playerCol)){
        playerCol->getLoot(lootType, lootAmount);
        Destroy();
    }
    
    // Add friction to velocity
    if(velocity.x > 0){
        velocity.x -= velocity.x * FRICTION;
        if(velocity.x < 0)
            velocity.x = 0;
    }
    else if(velocity.x < 0){
        velocity.x += -velocity.x * FRICTION;
        if(velocity.x > 0)
            velocity.x = 0;
    }
    
    if (velocity.y != 0)
        isGrounded = false;
}

bool Loot::collidesWith(Player* playerCol){
    Vector2f center = Vector2f(getPosition().x + getSize().x / 2.0 , getPosition().y + getSize().y / 2.0);
    Rect<float> otherBounds = playerCol->getSprite()->getGlobalBounds();
    
    if(center.x > otherBounds.left && center.x < otherBounds.left + otherBounds.width && center.y > otherBounds.top && center.y < otherBounds.top + otherBounds.height){
        return true;
    }
    
    return false;
}
