#ifndef START_H_INCLUDED
#define START_H_INCLUDED

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

class Start : public Object
{
public:
    Start();
    virtual ~Start();

    void Reset();
    void Draw();

    // Detect if cursor hovers over any of tower on menu
    // If so, return its type
    // Otherwise, return -1
    int MouseIn(int, int);

    // static function that detect if one point is on a line
    // This function is just used to simplify "MouseIn"
    static bool isInRange(int, int, int);

    // Check if current coin is not less than needed coin

private:
    ALLEGRO_BITMAP *love = NULL;
    ALLEGRO_FONT *menuFont;
    int HealthPoint = 10;
    int killedMonster = 0;
    std::string player_type;
};

#endif // START_H_INCLUDED
