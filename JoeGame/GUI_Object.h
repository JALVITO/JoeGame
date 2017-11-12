//
//  GUI_Object.hpp
//  JoeGame
//
//  Created by Adrian Mancilla on 11/11/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef GUI_Object_h
#define GUI_Object_h

#include <iostream>
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

class GUI_Object{
protected:
    Vector2f size;
    Sprite sprite;
    Vector2f position;
public:
    GUI_Object();
    GUI_Object(Vector2f _size, Vector2f _position, Texture* texture);
    void draw(RenderWindow* window);
};
#endif /* GUI_Object_h */
