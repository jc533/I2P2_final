#ifndef WITCH_H_INCLUDED
#define WITCH_H_INCLUDED

#include <stdio.h>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Object.h"
#include "Circle.h"
#include "global.h"
#include "Monster.h"


class Witch : public Monster{
public:
    Witch(int pos_x, int pos_y):Monster(pos_x,pos_y){
        defense=5;
        speed=2;
        attack_frequency=200000;
        attack_harm_point=2;
        attack_range = 200;
        //class_name="witch";
        strncpy(class_name, "Witch", 20);
        Load_Move();
    };
};


#endif // WITCH_H_INCLUDED
