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
    this->step = 0;

    // default direction is right
    direction = RIGHT;

    circle = new Circle(pos_x, pos_y, 20);

    //circle->x = (path.front() % 15) * grid_width + grid_width/2;
    //circle->y = (path.front() / 15) * grid_height + grid_height/2;
    circle->r = grid_width/2;

    direction_count[LEFT] = 1;
    direction_count[RIGHT] = 1;
    direction_count[UP] = 1;
    direction_count[DOWN] = 1;

    sprite_pos = 0;
    counter = 0;
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

void
Monster::Draw()
{
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

    //al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(196, 79, 79, 200));
}

bool
Monster::Update(Character *player){
    int target_x, target_y;
    counter = (counter + 1) % draw_frequency;
    if(counter == 0)
        sprite_pos = (sprite_pos + 1) % direction_count[direction];

    if(circle->r * circle->r *300 >= player_distance(player->get_player_pos(), circle)){
        return true;
    }
    return false;

}
void
Monster::Move(Character *player)
{
    int target_x, target_y;
    int self_x, self_y;
    self_x = circle->x;
    self_y = circle->y;
    counter = (counter + 1) % draw_frequency;
    if(counter == 0)
        sprite_pos = (sprite_pos + 1) % direction_count[direction];
    if(Update(player)){
        target_x = player->get_player_pos()->x;
        target_y = player->get_player_pos()->y;
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

        circle->x += speed * axis_x[direction];
        circle->y += speed * axis_y[direction];
    }
    //if(step + 1 < path.size())
    //{
        // coordinate of next grid
        //target_grid_x = (path[step] % 15) * grid_width + grid_width/2;
        //target_grid_y = (path[step] / 15) * grid_height + grid_height/2;

        /*if(circle->x == target_grid_x && circle->y == target_grid_y)
        {
            int cur_grid = path[step];
            int next_grid = path[step+1];
            int prev_direction = direction;

            switch(direction)
            {
                case LEFT:
                case RIGHT:
                    if(next_grid == cur_grid - 15)
                        direction = UP;
                    else if(next_grid == cur_grid + 15)
                        direction = DOWN;

                    break;
                case UP:
                case DOWN:
                    if(next_grid == cur_grid - 1)
                        direction = LEFT;
                    else if(next_grid == cur_grid + 1)
                        direction = RIGHT;

                    break;

            }

            step++;

            if(prev_direction != direction)
                sprite_pos = 0;

            // reach final grid and set end point
            if(step == path.size() - 1){
                end_x = circle->x + axis_x[direction] * (2 * grid_width);
                end_y = circle->y + axis_y[direction] * (2 * grid_height);
            }*/
        //}
    //}

    // when getting to end point, return true
    /*if(circle->x == end_x && circle->y == end_y)
        return true;*/

    //circle->x += speed * axis_x[direction];
    //circle->y += speed * axis_y[direction];

    // if not reaching end point, return false

}

/*bool
Monster::Subtract_HP(int harm_point)
{
    HealthPoint -= harm_point;

    return (HealthPoint <= 0);
}
*/
