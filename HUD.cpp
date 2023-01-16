#include "HUD.h"
#include "character.h"

class Character;

HUD::HUD(){
    double HealthPoint = 0;
    double base_health = 0;
    int Enemies;
    hudFont = al_load_ttf_font("pirulen.ttf", 12, 0);
}

HUD::~HUD(){
    al_destroy_font(hudFont);
}

void HUD::Draw(){

    al_draw_filled_rectangle(300, 20, 1300, 60, al_map_rgb(139, 0, 0));

    al_draw_filled_rectangle(298, 18, 1302, 20, al_map_rgb(255, 255, 255));
    al_draw_filled_rectangle(298, 60, 1302, 62, al_map_rgb(255, 255, 255));
    al_draw_filled_rectangle(298, 18, 300, 62, al_map_rgb(255, 255, 255));
    al_draw_filled_rectangle(1300, 18, 1302, 62, al_map_rgb(255, 255, 255));

    al_draw_filled_rectangle(150, 820, (HealthPoint / base_health) * 300 + 150, 830, al_map_rgb(160, 0, 0));

    //al_draw_filled_rectangle(1350, 20, 1500, 60, al_map_rgb(255, 255, 255));
    char buffer[50];
    sprintf(buffer, "Enemies left :%d", Enemies);
    al_draw_text(hudFont, al_map_rgb(255, 255, 255), 320, 34, 0, buffer);
}

void
HUD::Update(Character *player){
    HealthPoint = player->get_health();
    base_health = player->get_base_health();
    //std::cout << HealthPoint / base_health << '\n';
}
