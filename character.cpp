#include "character.h"


Character::Character(int pos_x = 0, int pos_y = 0)
{
    this->circle = new Circle(pos_x, pos_y, 70);
}

Character::~Character()
{
    delete circle;

    al_destroy_bitmap(img);
    /*al_destroy_bitmap(attack_img);

    for(auto&& child : this->attack_set) {
        delete child;
    }
    this->attack_set.clear();*/
}

void
Character::Draw()
{
    fprintf(stderr, "fuccccccccccccccck");
    int draw_x = circle->x - (TowerWidth[this->type]/2);
    int draw_y = circle->y - (TowerHeight[this->type] - (TowerWidth[this->type]/2));

    al_draw_bitmap(img, draw_x, draw_y, 0);
}



