#include "HUD.h"



HUD::HUD(){
    int HealthPoint = 100;
    int boss_health = 500;
    hudFont = al_load_ttf_font("pirulen.ttf", 12, 0);
}

void HUD::Draw(){

    al_draw_filled_rectangle(300, 20, 1300, 60, al_map_rgb(139, 0, 0));

    al_draw_filled_rectangle(298, 18, 1302, 20, al_map_rgb(255, 255, 255));
    al_draw_filled_rectangle(298, 60, 1302, 62, al_map_rgb(255, 255, 255));
    al_draw_filled_rectangle(298, 18, 300, 62, al_map_rgb(255, 255, 255));
    al_draw_filled_rectangle(1300, 18, 1302, 62, al_map_rgb(255, 255, 255));

    al_draw_filled_rectangle(150, 820, 450, 830, al_map_rgb(160, 0, 0));

    //al_draw_filled_rectangle(1350, 20, 1500, 60, al_map_rgb(255, 255, 255));
    char buffer[50];
    sprintf(buffer, "Boss Health :%d", boss_health);
    al_draw_text(hudFont, al_map_rgb(255, 255, 255), 320, 34, 0, buffer);
}
