#ifndef ASSASSIN_H_INCLUDED
#define ASSASSIN_H_INCLUDED

#include <stdio.h>
#include <string>
#include "Object.h"
#include "Circle.h"
#include "global.h"
#include "Monster.h"


class Assassin : public Monster{
public:
    Assassin(int pos_x, int pos_y):Monster(pos_x,pos_y){
        defense=5;
        speed=10;
        attack_frequency=10;
        attack_harm_point=5;
        class_name="assassin";
    };
};


#endif // ASSASSIN_H_INCLUDED
