#include "UI.h"
#include "Menu.h"

const int ThumbWidth = 600;
const int ThumbHeight = 600;
const int gapX = 100, gapY = 30;
const int offsetX = 150, offsetY = 150;


bool
UI::isInRange(int point, int startPos, int length){
    if(point >= startPos && point <= startPos + length)
        return true;
    return false;
}

int
UI::MouseIn(int mouse_x, int mouse_y){
    character_type = -1;
    for(int i=0; i < Num_ClassType; i++){
        int pos_x = offsetX + (ThumbWidth + gapX) * (i % 2);
        int pos_y = offsetY + (ThumbHeight + gapY) * (i / 2);
        if(isInRange(mouse_x, pos_x, ThumbWidth) && isInRange(mouse_y, pos_y, ThumbHeight)){
            character_type = i;
            break;
        }
    }
    return character_type;
}

UI::UI(){
    char filename[50];
    for(int i=0;i<Num_ClassType; i++){
        ALLEGRO_BITMAP *class_character;
        sprintf(filename, "./Tower/%s_Menu.png", TowerClass[i]);
        class_character = al_load_bitmap(filename);
        class_ui.push_back(class_character);
    }
    uiFont = al_load_ttf_font("pirulen.ttf", 12, 0); // load font
}

UI::~UI(){
    al_destroy_font(uiFont);
    for(int i=0; i < Num_ClassType; i++)
        al_destroy_bitmap(class_ui[i]);
    class_ui.clear();
}

void
UI::Draw(){

    char buffer[50];
    for(int i = 0; i < Num_ClassType; i++){
        int pos_x = offsetX + (ThumbWidth + gapX) * (i % 2);
        int pos_y = offsetY + (ThumbHeight + gapY) * (i / 2);
        //al_draw_bitmap(class_ui[i], pos_x, pos_y, 0);
        al_draw_filled_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 255, 255));
        if(i == character_type)
            al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 0, 0), 0);
        else
            al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 255, 255), 0);

    }


}
