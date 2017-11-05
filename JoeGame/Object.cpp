//
//  Object.cpp
//  JoeGame
//
//  Created by Juan Lizarraga on 11/4/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include "Object.h"

const float GRAVITY = 0.5;

Object::Object(){}

Object::Object(double _density, vector<int> &_type, Vector2f _size, Texture* texture){
    density = _density;
    type = _type;
    size = _size;
    acceleration = Vector2f();
    velocity = Vector2f();
    position = Vector2f();
    mass = density * pow((size.x * size.y), 1/5.0);
    theta = 0;
    sprite.setTexture(*texture);
    //sprite.setColor(Color(255, 255, 255, 255));
    sprite.setScale(size.x / 16.0, size.y / 16.0);
    sprite.setPosition(position);
}

Object::Object(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture) : Object(_density, _type, _size, texture){
    position = _position;
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
    // Add velocity to position on the x axis
    sprite.setPosition(position);
    // Check for collision with each of the provided objects
    for(int i = 0; i < colliders.size(); i++){
        collidesWith(colliders.at(i), 0);
    }
    // Add velocity to position on the y axis
    position.y += velocity.y;
    // Add velocity to position on the x axis
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
                    //underlap(otherBounds);
                    underlap(other, axis);
                    return true;
                }
    
    /*/
    if(sprite.getGlobalBounds().intersects((*other).sprite.getGlobalBounds())){
        underlap(other);
        return true;
    }
    /*/
    
    return false;
}

void Object::underlap(Object &other, int axis){
    if(!axis){
        if(velocity.x > 0 ){
            position.x -= position.x + size.x - other.sprite.getGlobalBounds().left;
        }
    
        if(velocity.x < 0 ){
            position.x += other.sprite.getGlobalBounds().left + other.sprite.getGlobalBounds().width - position.x;
        }
    }
    
    else{
        if(velocity.y > 0 ){
            position.y -= position.y + size.y - other.sprite.getGlobalBounds().top;
            isGrounded = true;
        }
    
        if(velocity.y < 0 ){
            position.y += other.sprite.getGlobalBounds().top + other.sprite.getGlobalBounds().height - position.y;
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





