#include "UI.h"

const int ThumbWidth = 50;
const int ThumbHeight = 50;
const int gapX = 40, gapY = 30;
const int offsetX = 30 + field_width, offsetY = 150;


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
    for(int i=0;i<Num_ClassType; i++)
    {
        ALLEGRO_BITMAP *class_character;
        sprintf(filename, "./Tower/%s_Menu.png", TowerClass[i]);
        class_character = al_load_bitmap(filename);
        class_ui.push_back(class_character);
    }
    uiFont = al_load_ttf_font("pirulen.ttf", 20, 0); // load font
}

UI::~UI()
{
    al_destroy_font(uiFont);

    for(int i=0; i < Num_ClassType; i++)
        al_destroy_bitmap(class_ui[i]);

    class_ui.clear();
}
void
UI::Draw(){
    char buffer[50];
    for(int i = 0; i < Num_ClassType; i++){



    }


}
