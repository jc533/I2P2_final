#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <list>
#include <time.h>
#include <utility>

#include "Level.h"
#include "HUD.h"
#include "UI.h"

#include "knight.h"
#include "ninja.h"
#include "assassin.h"
#include "bomb.h"
#include "witch.h"
#include "zombie.h"


#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7
#define GAME_LEVEL_FINISH 8

// clock rate
const float FPS = 60;

// total number of level
const int LevelNum = 4;

// 1 coin every 2 seconds
const int CoinSpeed = FPS * 2;
const int Coin_Time_Gain = 1;

class GameWindow
{
public:
    // constructor
    GameWindow();
    // each process of scene
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();

    int game_run();
    int game_update();

    void show_err_msg(int msg);
    void game_destroy();
    void game_start();
    // each drawing scene function
    void draw_running_map();
    void draw_choose();
    // process of updated event
    int process_event();
    // detect if mouse hovers over a rectangle
    bool mouse_hover(int, int, int, int);
    // detect if a tower will be constructed on road
    bool isOnRoad();

    Character* create_player(std::string);

    //Tower* create_tower(int);
    Monster* create_monster();
    HUD* hud = NULL;
public:
    bool initial = true;
private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *tower[Num_TowerType];
    //ALLEGRO_BITMAP *background = NULL;
    std::vector<ALLEGRO_BITMAP *> background;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Medium_font = NULL;
    ALLEGRO_FONT *Large_font = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *monster_pro = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *startSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *clearSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;

    LEVEL *level = NULL;

    UI *ui = NULL;
    //HUD *hud = NULL;

    std::vector<Monster*> monsterSet;
    Character *Player;
    std::string role;

    int Monster_Pro_Count = 0;
    int Coin_Inc_Count = 0;
    int mouse_x, mouse_y;
    int selectedTower = -1, lastClicked = -1;

    bool start = true;
    bool redraw = false;
    bool mute = false;
    bool win=false;
    bool end=false;
    bool can_choose = false;
};


#endif // MAINWINDOW_H_INCLUDED
