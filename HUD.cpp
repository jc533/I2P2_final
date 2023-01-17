#include "HUD.h"
#include "character.h"
#include "Level.h"


HUD::HUD(){
    double HealthPoint = 0;
    double base_health = 0;
    int Enemies;
    hudFont = al_load_ttf_font("pirulen.ttf", 12, 0);
    LargehudFont = al_load_ttf_font("pirulen.ttf", 48, 0);
    char filename[50];
    ALLEGRO_BITMAP *class_character;
    sprintf(filename, "./Knight/DOWN_0.png");
    class_character = al_load_bitmap(filename);
    selected_ui.push_back(class_character);
    sprintf(filename, "./Ninja/DOWN_0.png");
    class_character = al_load_bitmap(filename);
    selected_ui.push_back(class_character);

}

HUD::~HUD(){
    al_destroy_font(hudFont);
}

void HUD::Draw(){

    al_draw_filled_rectangle(300, 20, 300 + Enemies / total_enemies * 1000, 60, al_map_rgb(139, 0, 0));
    al_draw_rectangle(300, 20, 1300, 60, al_map_rgb(255, 255, 255), 3);
    al_draw_rectangle(150, 820, 450, 830, al_map_rgb(255, 255, 255), 3);
    al_draw_filled_rectangle(150, 820, (HealthPoint / base_health) * 300 + 150, 830, al_map_rgb(160, 0, 0));

    //al_draw_filled_rectangle(1350, 20, 1500, 60, al_map_rgb(255, 255, 255));
    char buffer[50];
    sprintf(buffer, "Enemies left :%d", Enemies);
    al_draw_text(hudFont, al_map_rgb(255, 255, 255), 320, 34, 0, buffer);
    al_draw_filled_circle(89, 820, 50, al_map_rgb(211, 211, 211));
    al_draw_circle(89, 820, 50, al_map_rgb(255, 255, 255), 3);
    if(type)
        al_draw_scaled_bitmap(selected_ui[1], 0, 0, al_get_bitmap_width(selected_ui[1]), al_get_bitmap_height(selected_ui[1]), 40, 780, 100, 100, 0);
    else
        al_draw_scaled_bitmap(selected_ui[0], 0, 0, al_get_bitmap_width(selected_ui[0]), al_get_bitmap_height(selected_ui[0]), 40, 780, 100, 100, 0);

}

void
HUD::Update(Character *player, int left, LEVEL *level){
    HealthPoint = player->get_health();
    base_health = player->get_base_health();
    type = player->GetType();
    total_enemies = level->get_Monster_Max();
    Enemies = left;
    //std::cout << HealthPoint / base_health << '\n';
}

void HUD::Level_reward(){
    al_draw_text(LargehudFont, al_map_rgb(255, 255, 255), 800, 300, 1, "Level cleared");
    al_draw_text(LargehudFont, al_map_rgb(255, 255, 255), 800, 400, 1, "Press 1 to add damage buff");
    al_draw_text(LargehudFont, al_map_rgb(255, 255, 255), 800, 500, 1, "Press 2 to add defense buff");
    al_draw_text(LargehudFont, al_map_rgb(255, 255, 255), 800, 600, 1, "Press 3 to restore health");
}

void HUD::win(){
    al_clear_to_color(al_map_rgb(219, 219, 219));
    al_draw_text(LargehudFont, al_map_rgb(255, 255, 255), 800, 500, 1, "YOU WIN");
    al_draw_text(LargehudFont, al_map_rgb(255, 255, 255), 800, 600, 1, "Left click to restart    Right click to exit");
}

void HUD::lose(){
    al_clear_to_color(al_map_rgb(219, 219, 219));
    al_draw_text(LargehudFont, al_map_rgb(255, 255, 255), 800, 500, 1, "YOU LOSE");
    al_draw_text(LargehudFont, al_map_rgb(255, 255, 255), 800, 600, 1, "Left click to restart    Right click to exit");
}
