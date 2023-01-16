#include "turret.h"


Turret::~Turret()
{
    delete circle;

    al_destroy_bitmap(img);
    al_destroy_bitmap(attack_img);

    for(auto&& child : this->attack_set) {
        delete child;
    }
    this->attack_set.clear();
}

void
Turret::Draw()
{
    int draw_x = circle->x - (TowerWidth[this->type]/2);
    int draw_y = circle->y - (TowerHeight[this->type] - (TowerWidth[this->type]/2));


    al_draw_bitmap(img, draw_x, draw_y, 0);

    for(unsigned int i=0; i<this->attack_set.size(); i++)
        this->attack_set[i]->Draw();

    if(isClicked)
    {
        al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(196, 79, 79, 200));
        al_draw_filled_circle(circle->x, circle->y, 2, al_map_rgb(0, 0, 0));
    }
}

bool
Turret::DetectAttack(Character *player)
{
    bool willAttack = false;
    Attack *attack;

    if(Circle::isOverlap(this->circle, player->getCircle()))
    {
        if(attack_counter == 0)
        {
            attack = new Attack(
                this->circle,
                player->getCircle(),
                this->attack_harm_point,
                this->attack_velocity,
                this->attack_img
            );

            this->attack_set.push_back(attack);
            willAttack = true;
        }

        attack_counter = (attack_counter + 1) % attack_frequency;
    }

    return willAttack;
}

bool
Turret::TriggerAttack(Character *player)
{
    bool isDestroyed = false;

    for(unsigned int i = 0; i < this->attack_set.size(); i++)
    {
        if(Circle::isOverlap(attack_set[i]->getCircle(), player->getCircle()))
        {
            /*TODO:*/
            /*1. Reduce the monster HP by the harm point*/
            /*2. Erase and delete the attack from attack set*/
            /*3. Return true if the monster's HP is reduced to zero*/
            isDestroyed = 0;//monster->Subtract_HP(attack_set[i]->getHarmPoint());
            attack_set.erase(attack_set.begin()+i);
            if(isDestroyed)
                return true;

        }
    }
    return false;
}

void
Turret::UpdateAttack()
{
    for(unsigned int i=0; i < this->attack_set.size(); i++)
    {
        if(!Circle::isOverlap(this->attack_set[i]->getCircle(), this->circle))
        {
            Attack *attack = this->attack_set[i];

            this->attack_set.erase(this->attack_set.begin() + i);
            i--;
            delete attack;
        }
    }
}
