#include "character.h"


Character::Character(int pos_x = 0, int pos_y = 0,int range=100)
{
    this->circle = new Circle(pos_x, pos_y, 70);
    this->weapon_range = new Circle(pos_x, pos_y, range);
}

Character::~Character()
{
    delete circle;

    al_destroy_bitmap(img);
}

void
Character::Update(){
    counter+=1;
    if(Count(dodge_fequency)){
        dodged = 0;
    }
    if(Count(attack_frequency)){
        attacked = 0;
    }
    switch(state){
        case Type::MOVE:
        Move();
        break;
        case Type::ATTACK:
        if(!attacked)
        Attack();
        break;
        case Type::DODGE:
        if(!dodged){
            Dodge();
        }
        break;
        case Type::IDLE:
        break;
    }
}
void
Character::SetState(Type next_state,int dir){
    state = next_state;
    direction = dir==-1?direction:dir;
}

void
Character::Move(){
    circle->x += speed * axis_x[direction];
    circle->y += speed * axis_y[direction];

}
void
Character::Attack(){attacked=1;}

void
Character::Dodge(){
    circle->x += 15 * speed * axis_x[direction];
    circle->y += 15 * speed * axis_y[direction];
    dodged = 1;
    SetState(Type::IDLE);
}
void
Character::Draw(){

    int draw_x = circle->x - (TowerWidth[this->type]/2);
    int draw_y = circle->y - (TowerHeight[this->type] - (TowerWidth[this->type]/2));
    char filename[50];
    sprintf(filename, "./Tower/%s.png", TowerClass[this->type]);
    img = al_load_bitmap(filename);
    al_draw_bitmap(img, draw_x, draw_y, 0);
}


Circle*
Character::get_player_pos(){
    return circle;
}

bool
Character::Count(int timer){
    if(counter%timer==0)return 1;
    return 0;
}

Circle* Character::get_attack_range(){
    return weapon_range;
}



