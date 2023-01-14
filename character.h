#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

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


class Monster;

class Character : public Object{
public:
    Character(int, int);
    virtual ~Character();

    // override virtual function "Object::Draw"
    void Draw();
    //void resetAttackCounter() { attack_counter = 0; }

    // update whole attack set
    // if any attack goes out of the range of tower, delete it
    // process if some of attack in set touches monster
    void Update();
    void Move();
    void Dodge();
    void Attack();

    int Detect(Monster*);
    void Subtract_HP(int);
    void Load_move();

    int getWidth() { return 40; }
    int getHeight() { return 40; }

    // show selected tower image on cursor position
    //static void SelectedTower(int, int, int);

protected:

    enum class Type {ATTACK,DODGE,MOVE,IDLE};
    enum class Buff {Enlarge,Shrink,Invisible};
    Type state;
    Buff buff_state;
    int defense;
    int speed;
    int direction;
    int direction_count[4];
    int size=1;
    int pos[2];
    int type;
    int attack_frequency;
    //int attack_counter;
    int attack_harm_point;
    //ALLEGRO_BITMAP *attack_img;

    // information of tower
    ALLEGRO_BITMAP* img;
    std::vector<ALLEGRO_BITMAP*> moveImg;

};

#endif // CHARACTER_H_INCLUDED
