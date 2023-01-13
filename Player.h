#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Object.h"
#include "Circle.h"
#include "global.h"
#include "ninja.h"
#include "knight.h"

class Player : public Character{
    ~Player();

    void Draw();
    bool Update();
    bool Move();
    int Detect(Monster*);
    bool Subtract_HP(int);

public:
    Character *player;
    Player(string type,int pos_x, int pos_y){
        if(type=="ninja"){
            player = new Ninja(pos_x, pos_y);
        }else if(type=="knight"){
            player = new Knight(pos_x, pos_y);
        }
    }
};

#endif // PLAYER_H_INCLUDED
