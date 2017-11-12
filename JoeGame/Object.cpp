//
//  Object.cpp
//  JoeGame
//
//  Created by Juan Lizarraga on 11/4/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include "Object.h"

Object::Object(){};

Object::Object(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture){
    type = _type;
    size = _size;
    acceleration = Vector2f();
    velocity = Vector2f();
    position = _position;
    mass = _mass;
    theta = 0;
    sprite.setTexture(*texture);
    isDestroyed = false;
    //sprite.setColor(Color(255, 255, 255, 255));
    sprite.setScale(size.x / 16.0, size.y / 16.0);
    sprite.setPosition(position);
}

void Object::update(){
    // Add gravity force
    addForce(Vector2f(0, GRAVITY * mass), 0);
    // Add acceleration to velocity
    velocity += acceleration;
    // Reset acceleration
    acceleration = Vector2f();
    // Add velocity to position
    position += velocity;
    // Add friction to velocity
    if(velocity.x > 0)
        velocity.x -= FRICTION;
    else if(velocity.x < 0)
        velocity.x += FRICTION;
    
    sprite.setPosition(position);
}

void Object::update(vector<Object> &colliders){
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
        collidesWith(colliders.at(i), 0);
    }
    // Add velocity to position on the y axis
    position.y += velocity.y;
    sprite.setPosition(position);
    // Check for collision with each of the provided objects
    for(int i = 0; i < colliders.size(); i++){
        collidesWith(colliders.at(i), 1);
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
void Object::draw(RenderWindow* window){
    (*window).draw(sprite);
}

bool Object::collidesWith(Object &other, int axis){
    Rect<float> ownBounds = sprite.getGlobalBounds();
    Rect<float> otherBounds = other.sprite.getGlobalBounds();
    
    if(ownBounds.left + ownBounds.width > otherBounds.left)
        if(ownBounds.left < otherBounds.left + otherBounds.width)
            if(ownBounds.top + ownBounds.height > otherBounds.top)
                if(ownBounds.top < otherBounds.top + otherBounds.height){
                    underlap(otherBounds, axis);
                    //underlap(other, axis);
                    return true;
                }
    
    return false;
}

void Object::underlap(Rect<float> &otherBounds, int axis){
    if(!axis){
        if(velocity.x > 0 ){
            position.x -= position.x + size.x - otherBounds.left;
        }
    
        if(velocity.x < 0 ){
            position.x += otherBounds.left + otherBounds.width - position.x;
        }
        
        velocity = Vector2f(0, velocity.y);
    }
    
    else{
        if(velocity.y > 0 ){
            position.y -= position.y + size.y - otherBounds.top;
            isGrounded = true;
        }
    
        if(velocity.y < 0 ){
            position.y += otherBounds.top + otherBounds.height - position.y;
        }
        
        velocity = Vector2f(velocity.x, 0);
    }
    
    sprite.setPosition(position);
    
}

void Object::addForce(Vector2f force){
    acceleration.x += (force.x / mass);
    acceleration.y += (force.y / mass);
}

void Object::addForce(Vector2f force, int index){
    acceleration.x += (force.x / mass) * type.at(index);
    acceleration.y += (force.y / mass) * type.at(index);
}

void Object::setVelocity(Vector2f _velocity){
    velocity = _velocity;
}

void Object::setVelocity(float _x, float _y){
    velocity.x = _x;
    velocity.y = _y;
}

Vector2f Object::getVelocity(){
    return velocity;
}

float Object::getVelocityX(){
    return velocity.x;
}
float Object::getVelocityY(){
    return velocity.y;
}

Sprite* Object::getSprite(){
    return &sprite;
}

Vector2f Object::getPosition(){
    return position;
}

void Object::setPosition(Vector2f _position){
    position = _position;
}

bool Object::isItDestroyed(){
    return isDestroyed;
}

void Object::Destroy(){
    isDestroyed = true;
}

Vector2f Object::getSize(){
    return size;
}

float Object::getAtan(Vector2f coordinates, bool radians){
    float angle = atan(coordinates.x / coordinates.y);
    
    if(!coordinates.x && coordinates.y < 0){
        
        angle = M_PI;
    }
    
    if (angle < 0){
        if (coordinates.x < 0)
            angle = -angle;
        else
            angle = M_PI - angle;
    }
    else{
        if (coordinates.x < 0)
            angle = M_PI - angle;
        else
            angle = -angle;
    }
    
    if(!radians)
        angle = angle*180/M_PI;
    
    return angle;
}



