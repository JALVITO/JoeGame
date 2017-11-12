//
//  GUI_Button.cpp
//  JoeGame
//
//  Created by Adrian Mancilla on 11/11/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>

#include "GUI_Button.h"

GUI_Button::GUI_Button(){}

GUI_Button::GUI_Button(Vector2f _size, Vector2f _position, Texture* texture, GUI_Text _text, Texture* _hoverSprite) : GUI_Object(_size, _position, texture){
    text = _text;
    //add hoversprite somehow
}
