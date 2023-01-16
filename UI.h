#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

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

class UI: public Object{
public:
    UI();
    virtual ~UI();
    void Draw();
    void update(Character*);
    void reset();
    int MouseIn(int, int);
    static bool isInRange(int, int, int);

private:
    std::vector<ALLEGRO_BITMAP*> class_ui;
    int character_type = -1;
    ALLEGRO_FONT *uiFont;
    ALLEGRO_FONT *uiLargeFont;




};

#endif // UI_H_INCLUDED
