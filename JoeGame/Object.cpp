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

Object::Object(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture){
    density = _density;
    type = _type;
    size = _size;
    acceleration = Vector2f();
    velocity = Vector2f();
    position = _position;
    mass = density / 100.0 * cbrt((size.x * size.y));
    theta = 0;
    sprite.setTexture(*texture);
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
    //acceleration = Vector2f(0, 0);
    
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

Sprite Object::getSprite(){
    return sprite;
}





