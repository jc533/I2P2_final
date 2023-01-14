#ifndef NINJA_H_INCLUDED
#define NINJA_H_INCLUDED

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
#include "character.h"

class Ninja : public Character{
public:
    Ninja(int pos_x, int pos_y):Character(pos_x,pos_y,100){
        defense=5;
        speed=10;
        attack_frequency=10;
        attack_harm_point=5;
        type=0;//"ninja";
        attack_range = 100;
    };
};



#endif