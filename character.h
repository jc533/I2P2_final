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

enum class Type {ATTACK,DODGE,MOVE,IDLE};
enum class Buff {Enlarge,Shrink,Invisible};
class Character : public Object{
public:
    Character(int, int, int);
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
    bool Count(int timer);
    void SetState(Type,int dir=-1);

    int Detect(Monster*);
    void Subtract_HP(int);
    void Load_move();

    int getWidth() { return 40; }
    int getHeight() { return 40; }
    Type GetState(){ return state;}
    int get_damage(){return damage;}
    Circle* get_player_pos();
    Circle* get_attack_range();
    // show selected tower image on cursor position
    //static void SelectedTower(int, int, int);

protected:

    Type state;
    Buff buff_state;
    int health_point;
    int damage=10;
    int defense;
    int speed;
    int direction=0;
    int direction_count[4];
    int size=1;
    int pos[2];
    int type;
    int attack_frequency=60;
    int dodge_fequency=60;
    bool dodged=0;
    bool attacked=0;
    unsigned int counter;
    int attack_range=40;
    //int attack_counter;
    int attack_harm_point;
    Circle *weapon_range;
    //ALLEGRO_BITMAP *attack_img;

    // information of tower
    ALLEGRO_BITMAP* img;
    std::vector<ALLEGRO_BITMAP*> moveImg;

};

#endif // CHARACTER_H_INCLUDED
