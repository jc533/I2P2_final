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
#include "Level.h"

class HUD : public Object{
public:
    HUD();
    virtual ~HUD();
    void Draw();
    void Update(Character*, int left, LEVEL*);
    void reset();
    double HealthPoint;
    void Level_reward();
    void win();
    void lose();
private:
    //int HealthPoint;
    int item_timer;
    double base_health;
    std::vector<ALLEGRO_BITMAP*> hud;
    ALLEGRO_FONT *hudFont;
    ALLEGRO_FONT *LargehudFont;
    int type;
    int Enemies;
    double total_enemies;
    std::vector<ALLEGRO_BITMAP*> selected_ui;
};

#endif // HUD_H_INCLUDED
