//
//  GUI_Object.cpp
//  JoeGame
//
//  Created by Adrian Mancilla on 11/11/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include "GUI_Object.h"

GUI_Object::GUI_Object(){}

GUI_Object::GUI_Object(Vector2f _size, Vector2f _position, Texture* texture){
    position = _position;
    size = _size;
    sprite.setTexture(*texture);
    sprite.setPosition(_position);
    //nose si aqui se ocupe el scale factor
    sprite.setScale(size.x / 16.0, size.y / 16.0);
}

void GUI_Object::draw(RenderWindow* window){
    (*window).draw(sprite);
}
