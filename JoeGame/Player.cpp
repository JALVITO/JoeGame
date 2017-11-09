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

Player::Player(){};

Player::Player(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, float _jumpForce, float _moveForce, Weapon* _weapon) : Entity(_density, _type, _size, _position, texture, _maxHp){
    jumpForce = _jumpForce;
    moveForce = _moveForce;
    weapon = *_weapon;
}

void Player::update(vector<Object> &colliders){
    Entity::update(colliders);
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
    
    float angle = atan((mousePos.x - weapon.getPosition().x) / (mousePos.y - weapon.getPosition().y));
    angle = angle*180/M_PI;
    
    if (angle < 0){
        if ((mousePos.x - weapon.getPosition().x) < 0)
            angle = -angle;
        else
            angle = 180 - angle;
    }
    else{
        if ((mousePos.x - weapon.getPosition().x) < 0)
            angle = 180 - angle;
        else
            angle = -angle;
    }
    
    weapon.setTheta(angle);
    cout << angle << endl;
    cout << "x: " << mousePos.x - weapon.getPosition().x << endl;
    cout << "y: " << mousePos.y - weapon.getPosition().y << endl;

    
    rayCast = RectangleShape(Vector2f(5,1000));
    rayCast.setFillColor(sf::Color::Red);
    rayCast.setPosition(weapon.getPosition());
    rayCast.rotate(angle);
    
};
