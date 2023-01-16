#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED

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


class Bomb : public Monster{
public:
    Bomb(int pos_x, int pos_y):Monster(pos_x,pos_y){
        defense=5;
        speed=10;
        attack_frequency=10;
        attack_harm_point = 50;
        //class_name="bomb";
        strncpy(class_name, "Wallbreaker", 20);
        Load_Move();
    };
};


#endif // BOMB_H_INCLUDED
