#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED

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


class Zombie : public Monster{
public:
    Zombie(int pos_x, int pos_y):Monster(pos_x,pos_y){
        defense=5;
        speed=3;
        attack_frequency=180;
        attack_harm_point=3;
        attack_range = 10;

        //class_name="zombie";
        strncpy(class_name, "Zombie", 20);
        Load_Move();
    };
};


#endif // ZOMBIE_H_INCLUDED
