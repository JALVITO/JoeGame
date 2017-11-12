//
//  Player.cpp
//  JoeGame
//
//  Created by Juan Lizarraga on 11/8/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include "Player.h"
#include <math.h>
#include "Bullet.h"
#include "Magnet.h"

Player::Player(){};

Player::Player(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, float _jumpForce, float _moveForce, Weapon* _weapon) : Entity(_mass, _type, _size, _position, texture, _maxHp){
    jumpForce = _jumpForce;
    moveForce = _moveForce;
    weapon = *_weapon;
    selfVelocity = Vector2f();
}

void Player::update(vector<Object> &objectCol, vector<Magnet> &magnetCol){
    // Add gravity force
    addForce(Vector2f(0, GRAVITY * mass), 0);
    // Add acceleration to velocity
    velocity += acceleration;
    // Reset acceleration
    acceleration = Vector2f();
    // Add velocity to position on the x axis
    position.x += velocity.x + selfVelocity.x;
    sprite.setPosition(position);
    // Check for collision with each of the provided objects
    for(int i = 0; i < objectCol.size(); i++){
        collidesWith(objectCol.at(i), 0);
    }
    
    for(int i = 0; i < magnetCol.size(); i++){
        collidesWith(magnetCol.at(i), 0);
    }
    // Add velocity to position on the y axis
    position.y += velocity.y + selfVelocity.y;
    sprite.setPosition(position);
    // Check for collision with each of the provided objects
    for(int i = 0; i < objectCol.size(); i++){
        collidesWith(objectCol.at(i), 1);
    }
    
    for(int i = 0; i < magnetCol.size(); i++){
        collidesWith(magnetCol.at(i), 1);
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
    
    if(hp <= 0)
        die();
    weapon.setPosition(getPosition());
    weapon.update();
    //pointWeapon();
}

void Player::draw(RenderWindow* window){
    Entity::draw(window);
    weapon.draw(window);
    pointWeapon(window);
    (*window).draw(rayCast);
}

void Player::pointWeapon(RenderWindow* window){
    Vector2i mousePos = sf::Mouse::getPosition(*window);
    
    float angle = Object::getAtan(Vector2f(mousePos.x - weapon.getPosition().x, mousePos.y - weapon.getPosition().y), false);
    
    rayCast = RectangleShape(Vector2f(1, 1000));
    rayCast.setFillColor(sf::Color::Red);
    rayCast.setPosition(weapon.getPosition());
    rayCast.rotate(angle);
    
    weapon.getSprite()->setRotation(angle + 90);
    
};

float Player::getJumpForce(){
    return jumpForce;
}
float Player::getMoveForce(){
    return moveForce;
}

void Player::fireWeapon(vector<Bullet> &bullets){
    weapon.fire(bullets);
}

Weapon* Player::getWeapon(){
    return &weapon;
}


