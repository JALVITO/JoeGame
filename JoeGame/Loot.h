//
//  Loot.h
//  JoeGame
//
//  Created by Guilherme Bittencourt de Borba on 11/13/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Loot_h
#define Loot_h

#include "Object.h"

class Player;

class Loot : public Object{
protected:
    int lootType, lootAmount;
public:
    Loot();
    Loot(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _lootType, int _lootAmount);
    void update(vector<Object> &colliders, Player* playerCol);
    bool collidesWith(Player* playerCol);
};

#endif /* Loot_h */
