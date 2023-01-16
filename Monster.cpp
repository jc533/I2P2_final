#include "Monster.h"
#include <iostream>
const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};

// set counter frequency of drawing moving animation
const int draw_frequency = 10;

int player_distance(Circle *player_pos, Circle *monster_pos){
    return (player_pos->x - monster_pos->x)*(player_pos->x - monster_pos->x) + (player_pos->y - monster_pos->y) * (player_pos->y - monster_pos->y);
}
Monster::Monster(int pos_x, int pos_y)
{
    //this->step = 0;

    // default direction is right
    direction = RIGHT;

    circle = new Circle(pos_x, pos_y, get_range());
    //std::cout << get_range();
    //circle->x = (path.front() % 15) * grid_width + grid_width/2;
    //circle->y = (path.front() / 15) * grid_height + grid_height/2;
    //circle->r = grid_width/2;

    direction_count[LEFT] = 1;
    direction_count[RIGHT] = 1;
    direction_count[UP] = 1;
    direction_count[DOWN] = 1;

    sprite_pos = 0;
    counter = 0;
    move_delay = 0;
    //strncpy(class_name, "Wolf", 20);
}

Monster::~Monster()
{

    for(unsigned int i=0; i<moveImg.size(); i++)
    {
        ALLEGRO_BITMAP *img = moveImg[i];

        moveImg.erase(moveImg.begin() + i);

        i--;
        al_destroy_bitmap(img);
    }
    moveImg.clear();

    delete circle;
}

void Monster::Load_Move()
{
    char buffer[50];

    for(int i=0; i < 4; i++)
    {
        for(int j=0; j<direction_count[i]; j++)
        {
            ALLEGRO_BITMAP *img;
            sprintf(buffer, "./%s/%s_%d.png", class_name, direction_name[i], j);

            img = al_load_bitmap(buffer);
            if(img)
                moveImg.push_back(img);
        }
    }
}

bool
Monster::Count(int timer){
    if(attack_counter%timer==0)return 1;
    return 0;
}

void
Monster::Draw(){
    int w, h;
    int offset = 0;

    // calculate the number of pictures before current direction
    for(int i=0; i<direction; i++)
        offset += direction_count[i];

    if(!moveImg[offset + sprite_pos])
        return;

    // get height and width of sprite bitmap
    w = al_get_bitmap_width(moveImg[offset + sprite_pos]);
    h = al_get_bitmap_height(moveImg[offset + sprite_pos]);


    // draw bitmap align grid edge
    al_draw_bitmap(moveImg[offset + sprite_pos], circle->x - w/2, circle->y - (h - grid_height/2), 0);
    al_draw_circle(circle->x, circle->y, get_range(), al_map_rgba(255, 255, 255, 0), 0);
    //al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(196, 79, 79, 200));
}

bool
Monster::Update(Character *player){
    //int target_x, target_y;
    counter = (counter + 1) % draw_frequency;
    if(counter == 0)
        sprite_pos = (sprite_pos + 1) % direction_count[direction];
    if(get_range() * get_range() * 500 >= player_distance(player->get_player_pos(), circle) && get_range() * get_range() *10 <= player_distance(player->get_player_pos(), circle)){
        //std::cout << get_range() << " " << get_range() <<'\n';
        return true;
    }
    return false;

}

bool
Monster::encircle(Character *player){
    if(get_range() * get_range() *15 >= player_distance(player->get_player_pos(), circle) && get_range() * get_range() *10 <= player_distance(player->get_player_pos(), circle)){
        return true;
    }
    return false;
}
void
Monster::Move(Character *player){
    attack_counter++;
    int target_x, target_y;
    int self_x, self_y;
    self_x = circle->x;
    self_y = circle->y;
    counter = (counter + 1) % draw_frequency;
    if(counter == 0)
        sprite_pos = (sprite_pos + 1) % direction_count[direction];
    //std::cout << "chase" << '\n';
    if(Update(player)){

        /*if(encircle(player)){
            int theta = rand()%360;
            target_x = player->get_player_pos()->x + cos(theta) * circle->r;
            target_y = player->get_player_pos()->y + sin(theta) * circle->r;
        }
        else{*/
            target_x = player->get_player_pos()->x;
            target_y = player->get_player_pos()->y;
        //}
        //target_x = player->get_player_pos()->x;
        //target_y = player->get_player_pos()->y;
        move_delay ++;
        if(move_delay == 5){
            if(abs(target_x - self_x) > abs(target_y - self_y) ){
                if(target_x - self_x > 0){
                    direction = RIGHT;
                }
                else{
                    direction = LEFT;
                }
            }
            else if(abs(target_x - self_x) < abs(target_y - self_y)){
                if(target_y - self_y > 0){
                    direction = DOWN;
                }
                else{
                    direction = UP;
                }
            }
            move_delay %= 5;
        }
        circle->x += speed * axis_x[direction];
        circle->y += speed * axis_y[direction];
    }
}
/*void
Monster::TriggerAttack(){
    bool isDestroyed = false;
    for(unsigned int i = 0; i < this->attack_set.size(); i++)
    {
        if(Circle::isOverlap(attack_set[i]->getCircle(), monster->getCircle()))
        {
            /*TODO:*/
            /*1. Reduce the monster HP by the harm point*/
            /*2. Erase and delete the attack from attack set*/
            /*3. Return true if the monster's HP is reduced to zero*/
            //isDestroyed = 0;//monster->Subtract_HP(attack_set[i]->getHarmPoint());
            //attack_set.erase(attack_set.begin()+i);
            //if(isDestroyed)
                //return true;

        //}
    //}
    //return false;
//}

bool
Monster::TriggerAttack(Character *player){
    if(attack_counter >= attack_delay){
        attack_counter = 0;
        return Circle::isOverlap(player->getCircle(),new Circle(this->circle->x,this->circle->y,get_range()));
    }
    else
        return false;
}

bool
Monster::DetectAttack(Character *player){
    //fprintf(stderr, "fuckkkk");
    if(player->GetState() == Type::ATTACK && Circle::isOverlap(player->get_attack_range(),this->getCircle())){
        return true;
    }
    return false;
}

bool
Monster::Subtract_HP(Character *player){
    HealthPoint -= player->get_damage();
    return (HealthPoint <= 0);
}

