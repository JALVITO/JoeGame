//
//  Magnet.cpp
//  JoeGame
//
//  Created by Guilherme Bittencourt de Borba on 11/10/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include "Magnet.h"
#include "Player.h"



Magnet::Magnet(){}

Magnet::Magnet(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, float _pullingForce) : Entity(_mass, _type, _size, _position, texture, _maxHp){
    
    pullingForce = _pullingForce;
    
    /*
    sprite.setColor(Color::Color(255, 255, 200));
    if(pullingForce < -200)
        sprite.setColor(Color::Color(150, 150, 150));
    */

}

void Magnet::excertForce(Object *other){
    float distanceX = (position.x + size.x/2.0) - (other->getPosition().x + other->getSize().x/2.0);
    float distanceY = (position.y + size.y/2.0) - (other->getPosition().y + other->getSize().y/2.0);
    
    float distance = distanceX * distanceX + distanceY * distanceY;
    
    float scalarForce = pullingForce / distance;
    
    float theta = Object::getAtan(Vector2f(distanceX, distanceY));
    Vector2f force = Vector2f(scalarForce * sin(theta), -scalarForce * cos(theta));
    
    
    other->addForce(force, 1);
    
}

void Magnet::update(vector<Object> &objectCol, vector<Bullet>  &bulletCol, Player* playerCol, vector<Enemy> &enemyCol){
    for(int i = 0; i < objectCol.size(); i++){
        excertForce(&objectCol.at(i));
    }
    
    for(int i = 0; i < bulletCol.size(); i++){
        excertForce(&bulletCol.at(i));
    }
    
    excertForce(playerCol);
    
    for(int i = 0; i < enemyCol.size(); i++){
        excertForce(&enemyCol.at(i));
    }
    
    if(hp <= 0)
        die();
}

void Magnet::update(vector<Loot> &lootCol){
    for(int i = 0; i < lootCol.size(); i++){
        excertForce(&lootCol.at(i));
    }
    
    if(hp <= 0)
        die();
}
