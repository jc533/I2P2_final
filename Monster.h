#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "Object.h"
#include "Circle.h"
#include "global.h"
#include "character.h"

class Character;
class Monster: public Object {
public:
    Monster(int, int);
    virtual ~Monster();

    // Draw image per frame
    // override virtual function "Object::Draw"
    void  Draw();
    // Load bitmaps of animation image into container "moveImg"
    void  Load_Move();
    // Update monster position per frame
    // And detect if it reaches end point but not destroyed
    bool  Move(Character*);
    // functions that return informations of monster
    int  getDir() { return direction; }
    bool  Subtract_HP(int);
    // update whole attack set
    // detect if tower needs to attack some monster
    bool DetectAttack(Character*);
    // process if some of attack in set touches monster
    bool TriggerAttack();
    bool Update(Character*);

protected:
    int direction_count[4];
    int HealthPoint;
    int speed;
    int defense;
    int attack_frequency;
    int attack_harm_point;
    //int worth = 10;
    //int score = 100;
    char class_name[20];
private:
    // direction and index for "path"
    unsigned int step;
    int direction;
    // end point
    int end_x, end_y;
    // animation counter
    int counter;
    // animation image of current direction
    int sprite_pos;

    // set of animation images
    std::vector<ALLEGRO_BITMAP*> moveImg;
    //path on map

};


#endif // MONSTER_H_INCLUDED
