#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "Object.h"
#include "Circle.h"
#include "global.h"
#include "character.h"

class HUD : public Object{
public:
    HUD();
    virtual ~HUD();
    void Draw();
    void Update(Character*);
    void reset();
    double HealthPoint;
private:
    //int HealthPoint;
    int item_timer;
    double base_health;
    std::vector<ALLEGRO_BITMAP*> hud;
    ALLEGRO_FONT *hudFont;
    int type;
    int Enemies;
};

#endif // HUD_H_INCLUDED
