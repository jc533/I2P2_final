#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <stdio.h>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Object.h"
#include "Circle.h"
#include "global.h"

class Character : public Object{
public:
    Character(int, int);
    virtual ~Character();

    // override virtual function "Object::Draw"
    virtual void Draw();
    //void resetAttackCounter() { attack_counter = 0; }

    // update whole attack set
    // if any attack goes out of the range of tower, delete it
    // process if some of attack in set touches monster
    virtual bool Update();
    virtual bool Move();
    virtual int Detect(Enemy*);
    virtual  bool Subtract_HP(int);

    virtual int getWidth() { return 40; }
    virtual int getHeight() { return 40; }

    // show selected tower image on cursor position
    //static void SelectedTower(int, int, int);

protected:

    enum class Type {ATTACK,DODGE,MOVE};
    Type state;
    int defense;
    int speed;
    int direction;
    int direction_count[4];
    string type;
    int attack_frequency;
    //int attack_counter;
    int attack_harm_point;
    //ALLEGRO_BITMAP *attack_img;

    // information of tower
    ALLEGRO_BITMAP std::vector<*img>;
};

#endif // CHARACTER_H_INCLUDED
