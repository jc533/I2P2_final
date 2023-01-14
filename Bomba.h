#ifndef BOMBA_H_INCLUDED
#define BOMBA_H_INCLUDED

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

class Bomba : public Object{
public:
    Bomba(int, int);
    virtual ~Bomba();
    void Draw();
private:
    int damage;
    int amount;

};

#endif // BOMBA_H_INCLUDED
