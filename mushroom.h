#ifndef MUSHROOM_H_INCLUDED
#define MUSHROOM_H_INCLUDED


#include "global.h"
#include "Circle.h"
#include "Object.h"
#include "item.h"
#include <stdio.h>

class Enlarge : public Item {
public:
    Enlarge(int pos_x, int pos_y):Item(pos_x, pos_y){
        time = 60;
        type = "enlarge";
        amount = 1;
    }
};

#endif // MUSHROOM_H_INCLUDED
