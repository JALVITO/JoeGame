//
//  Bullet.h
//  JoeGame
//
//  Created by Adrian Mancilla on 11/8/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Bullet_h
#define Bullet_h
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"

class Bullet : public Object{
protected:
    int damage;
    Vector2f center;
    bool isPlayer;
public:
    Bullet();
    Bullet(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _damage, bool isPlayer);
    void update(vector<Object> &objectcol, vector<Player> &playercol, vector<Enemy> &enemycol);
    void DealDamage(Entity &other, int _damage);
    bool collidesWith(Object &other);

};

#endif /* Bullet_h */
