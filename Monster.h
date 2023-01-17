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

    void Move(Character*);
    // functions that return informations of monster
    int  getDir() { return direction; }
    bool Subtract_HP(Character*);
    // update whole attack set
    int get_damage() { return attack_harm_point; }
    int get_range() {return attack_range; }
    int get_attack_delay() { return attack_frequency;}
    bool DetectAttack(Character*);
    // process if some of attack in set touches monster
    bool TriggerAttack(Character*);
    bool Update(Character*);
    bool is_dead();
    bool encircle(Character*);
    bool Count(int);
    char * get_class_name(){return class_name;}
protected:
    int direction_count[4];
    int HealthPoint;
    int speed;
    int defense;
    int attack_frequency;
    int attack_harm_point;
    int attack_range;
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
    int attack_counter;
    // animation image of current direction
    int sprite_pos;
    unsigned int move_delay;
    unsigned int attack_delay;
    // set of animation images
    std::vector<ALLEGRO_BITMAP*> moveImg;
    //path on map

};


#endif // MONSTER_H_INCLUDED
