#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include <stdio.h>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "global.h"
#include "Object.h"
#include "Circle.h"

class Weapon : public Object{
public:
    Weapon(int, int);
    virtual ~Weapon();
    void Draw();
protected:
    int Damage;


};

#endif // WEAPON_H_INCLUDED
