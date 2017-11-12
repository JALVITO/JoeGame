//
//  GUI_Text.cpp
//  JoeGame
//
//  Created by Adrian Mancilla on 11/11/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>

#include "GUI_Text.h"

GUI_Text::GUI_Text(){}

GUI_Text::GUI_Text(Vector2f _position, string _text, int _fontsize, Font* _font, Color _color){
    text.setFont(*_font);
    text.setString(_text);
    text.setCharacterSize(_fontsize);
    text.setFillColor(_color);
    text.setPosition(_position);
    //no se si aqui se ocupe el scale factor.
    //text.setScale(_size.x / 16.0, _size.y / 16.0);
}

void GUI_Text::draw(RenderWindow* window){
    (*window).draw(text);
}
