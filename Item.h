#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <stdio.h>
#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Object.h"
#include "Circle.h"
#include "global.h"
#include "Monster.h"


class Item : public Object{
public:
    Item(int, int);
    ~Item();

    // override virtual function "Object::Draw"
    void Draw();
    //void resetAttackCounter() { attack_counter = 0; }

    // update whole attack set
    // if any attack goes out of the range of tower, delete it
    // process if some of attack in set touches monster
    bool Move();

    int getWidth() { return 40; }
    int getHeight() { return 40; }

    // show selected tower image on cursor position
    //static void SelectedTower(int, int, int);

protected:

    int width;
    int height;
    int time;
    int amount;
    std::string type;
    //int attack_counter;
    //ALLEGRO_BITMAP *attack_img;

    // information of tower
    ALLEGRO_BITMAP *img;
};

#endif // CHARACTER_H_INCLUDED
