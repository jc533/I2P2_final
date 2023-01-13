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

enum {LEFT=0, RIGHT, UP, DOWN};

class Monster: public Object {
public:
    Monster(std::vector<int> path);
    virtual ~Monster();

    // Draw image per frame
    // override virtual function "Object::Draw"
    void virtual Draw();
    // Load bitmaps of animation image into container "moveImg"
    void virtual Load_Move();

    // Update monster position per frame
    // And detect if it reaches end point but not destroyed
    bool virtual Move();

    // functions that return informations of monster
    int virtual getDir() { return direction; }
    int virtual getWorth() { return worth; }
    int virtual getScore() { return score; }
    bool virtual Subtract_HP(int);
    // update whole attack set
    // detect if tower needs to attack some monster
    bool virtual DetectAttack(Player*);
    // process if some of attack in set touches monster
    bool virtual TriggerAttack();
    int virtual State();

protected:
    int direction_count[4];
    int HealthPoint;
    int speed;
    int defense;
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
    // path on map
    std::vector<int> path;

};


#endif // MONSTER_H_INCLUDED
