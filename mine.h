#ifndef MINE_H_INCLUDED
#define MINE_H_INCLUDED

#include <stdio.h>
#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Object.h"
#include "Circle.h"
#include "global.h"
#include "Item.h"


class Mine : public Item{
    public:
    Mine(int pos_x,int pos_y):Item(pos_x,pos_y){
        time=0;
        amount=1;
        type="mine"
    }
};

#endif // CHARACTER_H_INCLUDED
