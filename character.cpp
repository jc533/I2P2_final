#include "character.h"
#include <iostream>

Character::Character(int pos_x = 0, int pos_y = 0,int range = 50)
{
    this->circle = new Circle(pos_x, pos_y, 70);
    this->weapon_range = new Circle(pos_x, pos_y, range);
    direction_count[LEFT] = 3;
    direction_count[RIGHT] = 3;
    direction_count[UP] = 3;
    direction_count[DOWN] = 3;

    std::cout << range << '\n';
}

Character::~Character()
{
    for(unsigned int i=0; i<moveImg.size(); i++){
        ALLEGRO_BITMAP *img = moveImg[i];

        moveImg.erase(moveImg.begin() + i);

        i--;
        al_destroy_bitmap(img);
    }
    moveImg.clear();
    delete circle;
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
    //std::cout << attack_frequency<<'\n';
    if(!attacked){
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
    weapon_range->x = circle->x;
    weapon_range->y = circle->y;
}
void
Character::Attack(){
    attacked=1;
    std::cout << "shuuuu boooom !" <<'\n';
    SetState(Type::IDLE);
}

void
Character::Dodge(){
    circle->x += 15 * speed * axis_x[direction];
    circle->y += 15 * speed * axis_y[direction];
    dodged = 1;
    SetState(Type::IDLE);
}
void
Character::Draw(){

    /*char filename[50];
    sprintf(filename, "./Tower/%s.png", TowerClass[this->type]);
    //std::cout << filename << '\n';
    img = al_load_bitmap(filename);
    al_draw_bitmap(img, draw_x, draw_y, 0);*/


    int w, h;
    int offset = 0;
    int sprite_pos=0;
    // calculate the number of pictures before current direction
    for(int i=0; i<direction; i++)
        offset += direction_count[i];
    if(attacked){
        sprite_pos=1;
        if(counter%10<=5&&counter%10>=0)sprite_pos=2;
    }
    if(!moveImg[offset+sprite_pos])
        return;
    //std::cout << sprite_pos+offset << '\n';
    // get height and width of sprite bitmap
    w = al_get_bitmap_width(moveImg[offset+sprite_pos]);
    h = al_get_bitmap_height(moveImg[offset+sprite_pos]);
    int draw_x = circle->x - (w/2);
    int draw_y = circle->y - (h - (w/2));


    al_draw_scaled_bitmap(moveImg[offset+sprite_pos], 0, 0, w, h, draw_x, draw_y, w * 2, h * 2, 0);


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

bool
Character::Subtract_HP(int dmg){
    health_point -= dmg * (defense / (defense + 15.0));
    //std::cout << health_point << '\n';
    return health_point<=0;
}

void Character::Load_Move(){
    char buffer[50];

    for(int i=0; i < 4; i++){
        for(int j=0; j<direction_count[i]; j++){
            ALLEGRO_BITMAP *img;
            sprintf(buffer, "./%s/%s_%d.png", class_name, direction_name[i], j);
            //std::cout << buffer << " " << moveImg.size()<<'\n';
            img = al_load_bitmap(buffer);
            if(img)
                moveImg.push_back(img);
        }
    }
}
