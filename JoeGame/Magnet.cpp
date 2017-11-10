//
//  Magnet.cpp
//  JoeGame
//
//  Created by Guilherme Bittencourt de Borba on 11/10/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include "Magnet.h"



Magnet::Magnet(){}

Magnet::Magnet(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, float _pullingForce) : Entity(_density, _type, _size, _position, texture, _maxHp){
    
    pullingForce = _pullingForce;
}

void Magnet::excertForce(Object *other){
    float distance = sqrt(pow((position.x - other->getPosition().x), 2) + pow(position.y - other->getPosition().y, 2));
    
    if (distance < 75)
        distance = 75;
    
    Vector2f force = Vector2f(pullingForce * (position.x - other->getPosition().x) / (distance * distance), pullingForce * (position.y - other->getPosition().y) / (distance * distance));
    
    
    other->addForce(force, 1);
    
}

void Magnet::update(vector<Object> &objectCol, vector<Bullet>  &bulletCol, vector<Player> &playerCol, vector<Enemy> &enemyCol){
    for(int i = 0; i < objectCol.size(); i++){
        excertForce(&objectCol.at(i));
    }
    
    for(int i = 0; i < bulletCol.size(); i++){
        excertForce(&bulletCol.at(i));
    }
    
    for(int i = 0; i < playerCol.size(); i++){
        excertForce(&playerCol.at(i));
    }
    
    for(int i = 0; i < enemyCol.size(); i++){
        excertForce(&enemyCol.at(i));
    }
}
