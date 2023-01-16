#include "UI.h"

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

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

    ALLEGRO_BITMAP *class_character;
    sprintf(filename, "./Knight/DOWN_0.png");
    class_character = al_load_bitmap(filename);
    class_ui.push_back(class_character);

    sprintf(filename, "./Ninja/DOWN_0.png");
    class_character = al_load_bitmap(filename);
    class_ui.push_back(class_character);

    uiFont = al_load_ttf_font("Anton-Regular.ttf", 24, 0); // load font
    uiLargeFont = al_load_ttf_font("Orbitron-Black.ttf", 60, 0);
}

UI::~UI(){
    al_destroy_font(uiFont);
    for(int i=0; i < Num_ClassType; i++)
        al_destroy_bitmap(class_ui[i]);
    class_ui.clear();
}

void
UI::Draw(){
    //al_draw_filled_rectangle(100, 100, 700, 700, al_map_rgb(255, 255, 255));
    char buffer[50];
    for(int i = 0; i < Num_ClassType; i++){
        int pos_x = offsetX + (ThumbWidth + gapX) * (i % 2);
        int pos_y = offsetY + (ThumbHeight + gapY) * (i / 2);

        //al_draw_filled_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 255, 255));
        if(i == character_type)
            al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 0, 0), 0);
        else
            al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 255, 255), 0);
        //al_draw_bitmap(class_ui[i], pos_x, pos_y, 0);
        al_draw_scaled_bitmap(class_ui[i], 0, 0, al_get_bitmap_width(class_ui[i]), al_get_bitmap_height(class_ui[i]), pos_x, pos_y+100, 600, 600, 0);

        al_draw_text(uiLargeFont, WHITE, 800, 800, 1, "Left click for knight   Right click for ninja");
    }


}

