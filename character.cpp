#include "character.h"


Character::Character(int pos_x = 0, int pos_y = 0)
{
    this->circle = new Circle(pos_x, pos_y, 70);
}

Character::~Character()
{
    delete circle;

    al_destroy_bitmap(img);
}

void
Character::Update(){
    switch(state){
        case Type::MOVE:
        Move();
        break;
        case Type::ATTACK:
        Attack();
        break;
        case Type::DODGE:
        Dodge();
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
    switch (direction){
        case UP:
        circle->y -= speed;
        break;
        case DOWN:
        circle->y += speed;
        break;
    }
}
void
Character::Attack(){
    
}
void
Character::Dodge(){
    
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





