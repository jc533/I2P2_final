#ifndef TURRET_H_INCLUDED
#define TURRET_H_INCLUDED

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Object.h"
#include "Attack.h"
#include "Circle.h"
#include "Monster.h"
#include "global.h"

class Turret : public Monster{
public:
    Turret(int pos_x, int pos_y):Monster(pos_x,pos_y){
        defense=5;
        speed=10;
        attack_frequency=10;
        attack_harm_point=5;
        //class_name="turret";
        strncpy(class_name, "Wolf", 20);
    };
    virtual ~Turret();

    // override virtual function "Object::Draw"
    void Draw();
    void resetAttackCounter() { attack_counter = 0; }
    void ToggleClicked() { isClicked = !isClicked; }

    // update whole attack set
    // if any attack goes out of the range of tower, delete it
    void UpdateAttack();
    // detect if tower needs to attack some monster
    bool DetectAttack(Character*);
    // process if some of attack in set touches monster
    bool TriggerAttack(Character*);

    int attack_frequency = 20;
    int attack_counter = 0;
    int attack_harm_point = 5;
    int attack_velocity = 10;
    ALLEGRO_BITMAP *attack_img;
    std::vector<Attack*> attack_set;

    // information of tower
    int type;
    bool isClicked = false;
    ALLEGRO_BITMAP *img;
};



#endif // TURRET_H_INCLUDED
