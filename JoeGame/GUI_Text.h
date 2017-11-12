//
//  GUI_Text.h
//  JoeGame
//
//  Created by Adrian Mancilla on 11/11/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef GUI_Text_h
#define GUI_Text_h

#include <iostream>
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

class GUI_Text{
protected:
    Text text;
public:
    GUI_Text();
    GUI_Text(Vector2f _position, string _text, int _fontsize, Font* _font, Color _color);
    void draw(RenderWindow* window);
};

#endif /* GUI_Text_h */
