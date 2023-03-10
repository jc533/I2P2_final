#ifndef KNIGHT_H_INCLUDED
#define KNIGHT_H_INCLUDED

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

class Knight : public Character{
public:
    Knight(int pos_x, int pos_y):Character(pos_x,pos_y,200){
        defense=10;
        speed=5;
        attack_frequency=75;
        attack_range = 75;
        attack_harm_point=10;
        health_point = 100;
        base_health = health_point;
        type = 0;
        strncpy(class_name, "Knight", 20);
        Load_Move();
    };
};



#endif
