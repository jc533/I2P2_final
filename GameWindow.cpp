#include "GameWindow.h"
#include "global.h"
#include <iostream>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)ddd
#define BLUE al_map_rgb(77, 129, 179)

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))

const int ThumbWidth = 600;
const int ThumbHeight = 600;
const int gapX = 100, gapY = 30;
const int offsetX = 150, offsetY = 150;
bool start = true;
float Attack::volume = 1.0;

void set_attack_volume(float volume)
{
    Attack::volume = volume;
}

bool compare(Tower *t1, Tower *t2)
{
    return (t1->getY() <= t2->getY());
}

void
GameWindow::game_init()
{
    char buffer[50];

    icon = al_load_bitmap("./icon.png");
    background = al_load_bitmap("./StartBackground.jpg");

    for(int i = 0; i < Num_TowerType; i++)
    {
        sprintf(buffer, "./Tower/%s.png", TowerClass[i]);
        tower[i] = al_load_bitmap(buffer);
    }

    al_set_display_icon(display, icon);
    al_reserve_samples(3);

    sample = al_load_sample("cat-meow.mp3");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());

    sample = al_load_sample("BackgroundMusic.ogg");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());

    level = new LEVEL(1);
    menu = new Menu();
    hud = new HUD();
    ui = new UI();
    //game_start();
    //draw_choose();
    Player = NULL;
}

bool
GameWindow::mouse_hover(int startx, int starty, int width, int height){
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;
    return false;
}

/*Player*/
Character*
GameWindow::create_player(std::string type){
    Character* p=NULL;
    if(type=="ninja"){
        p = new Ninja(100,100);
    }else if(type=="knight"){
        p = new Knight(100,100);
    }
    return p;
}

Monster*
GameWindow::create_monster(){
    Monster *m = NULL;
    std::pair<int,int> original_pos;
    if(level->MonsterNum[ASSASSIN]){
        level->MonsterNum[ASSASSIN]--;
        original_pos = level->MonsoterPos[ASSASSIN];
        //std::cout << original_pos.first << " " << original_pos.second <<'\n';
        m = new Assassin(original_pos.first,original_pos.second);
    }
    else{
        al_stop_timer(monster_pro);
    }
    return m;
}

void
GameWindow::game_play()
{
    int msg;

    srand(time(NULL));

    msg = -1;
    game_reset();
    game_start();
    //game_begin();

    while(msg != GAME_EXIT)
    {
        msg = game_run();
    }
    std::cout <<"bloody hell" <<'\n';
    show_err_msg(msg);
}

void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / FPS);
    monster_pro = al_create_timer(1.0 / FPS);

    if(timer == NULL || monster_pro == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(monster_pro));

    game_init();
}

void
GameWindow::game_begin(){
    printf(">>> Start Level[%d]\n", level->getLevel());
    draw_running_map();

    al_play_sample_instance(startSound);
    while(al_get_sample_instance_playing(startSound));
    al_play_sample_instance(backgroundSound);

    al_start_timer(timer);
    al_start_timer(monster_pro);
}
void
GameWindow::game_start(){
    draw_running_map();
    al_start_timer(timer);
}

int
GameWindow::game_run(){
    int msg = GAME_CONTINUE;
    if (!al_is_event_queue_empty(event_queue)) {
        msg = process_event();
    }
    switch (msg){
    case GAME_NEXT_LEVEL:
        std::cout << "next" <<'\n';
        level->setLevel(level->getLevel()+1);
        game_reset();
        game_begin();
        break;
    default:
        //std::cout << msg << ' ' << GAME_NEXT_LEVEL <<'\n';
        break;
    }
    return msg;
}

int
GameWindow::game_update(){
    int i = 0;
    if(Player){
        Player->Update();
        for(auto mon: monsterSet){
            if(mon->DetectAttack(Player)){
                if(mon->Subtract_HP(Player)){
                    //std::cout << "die die die" << '\n';
                    monsterSet.erase(monsterSet.begin() + i++);
                }
            }
            mon->Move(Player);
            if(mon->get_attack_delay()){
                if(mon->TriggerAttack(Player)){
                    if(Player->Subtract_HP(mon->get_damage())){
                        std::cout << "You die" << '\n';
                        return GAME_EXIT;
                    }
                }

            }
        }
    }

    return GAME_CONTINUE;
}
/*void
GameWindow::game_start(){
    al_clear_to_color(al_map_rgb(100, 100, 100));
    draw_choose();
    std::cout << "are you fucking running" << '\n';
}*/
void
GameWindow::game_reset(){
    // reset game and begin
    /*for(auto&& child : towerSet) {
        delete child;
    }*/
    //towerSet.clear();
    monsterSet.clear();
    selectedTower = -1;
    lastClicked = -1;
    Coin_Inc_Count = 0;
    Monster_Pro_Count = 0;
    mute = false;
    redraw = false;
    menu->Reset();

    // stop sample instance
    al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(startSound);

    // stop timer
    al_stop_timer(timer);
    al_stop_timer(monster_pro);
}

void
GameWindow::game_destroy()
{
    game_reset();
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_timer(timer);
    al_destroy_timer(monster_pro);

    for(int i=0;i<5; i++)
        al_destroy_bitmap(tower[i]);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);

    al_destroy_sample(sample);
    al_destroy_sample_instance(startSound);
    al_destroy_sample_instance(backgroundSound);

    delete level;
    delete menu;
    delete hud;
    delete Player;
    delete ui;
}

int
GameWindow::process_event()
{

    int instruction = GAME_CONTINUE;
    // offset for pause window
    //int offsetX = field_width/2 - 200;
    //int offsetY = field_height/2 - 200;
    static bool key_state[ALLEGRO_KEY_MAX];
    al_wait_for_event(event_queue, &event);
    redraw = false;


    if(event.type == ALLEGRO_EVENT_TIMER) {
        //std::cout << "its time to stop" << '\n';
        if(event.timer.source == timer) {
            redraw = true;
            //std::cout << monsterSet.size() << '\n';
            //std::cout << "are you in" << '\n';
            //std::cout << !al_get_timer_started(monster_pro) << '\n';
            if(monsterSet.size() == 0 && !al_get_timer_started(monster_pro) && !start){
                al_stop_timer(timer);
                //std::cout << "go next" << '\n';
                return GAME_NEXT_LEVEL;
            }

        }
        else {
            if(Monster_Pro_Count == 0) {
                Monster *m = create_monster();
                if(m != NULL)
                    monsterSet.push_back(m);
            }
            Monster_Pro_Count = (Monster_Pro_Count + 1) % level->getMonsterSpeed();
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && start) {
        redraw = true;
        if(event.mouse.button == 1) {
            //std::cout << "im in" << '\n';
            Player = create_player("knight");
            start = false;
            game_begin();
        }
        else if(event.mouse.button == 2){
            Player = create_player("ninja");
            start = false;
            //std::cout << "hiiiiiii" << '\n';
            game_begin();
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        //fprintf(stderr,"pressed %d\n",event.keyboard.keycode);
        switch(event.keyboard.keycode) {

            case ALLEGRO_KEY_P:
                /*TODO: handle pause event here*/

                if(al_get_timer_started(timer))
                    al_stop_timer(timer);
                else
                    al_start_timer(timer);
                if(al_get_timer_started(monster_pro))
                    al_stop_timer(monster_pro);
                else
                    al_start_timer(monster_pro);
                break;
            case ALLEGRO_KEY_M:
                mute = !mute;
                if(mute)
                    al_stop_sample_instance(backgroundSound);
                else
                    al_play_sample_instance(backgroundSound);
                break;
            case ALLEGRO_KEY_W:
                key_state[ALLEGRO_KEY_W]=1;
                break;
            case ALLEGRO_KEY_A:
                key_state[ALLEGRO_KEY_A]=1;
                break;
            case ALLEGRO_KEY_S:
                key_state[ALLEGRO_KEY_S]=1;
                break;
            case ALLEGRO_KEY_D:
                key_state[ALLEGRO_KEY_D]=1;
                break;
            case ALLEGRO_KEY_E:
                key_state[ALLEGRO_KEY_E]=1;
                break;
            case ALLEGRO_KEY_SPACE:
                key_state[ALLEGRO_KEY_SPACE]=1;
                break;
        }
    }else if(event.type == ALLEGRO_EVENT_KEY_UP) {
        switch(event.keyboard.keycode) {
             case ALLEGRO_KEY_W:
                key_state[ALLEGRO_KEY_W]=0;
                Player->SetState(Type::IDLE);
                break;
            case ALLEGRO_KEY_A:
                key_state[ALLEGRO_KEY_A]=0;
                Player->SetState(Type::IDLE);
                break;
            case ALLEGRO_KEY_S:
                key_state[ALLEGRO_KEY_S]=0;
                Player->SetState(Type::IDLE);
                break;
            case ALLEGRO_KEY_D:
                key_state[ALLEGRO_KEY_D]=0;
                Player->SetState(Type::IDLE);
                break;
            case ALLEGRO_KEY_E:
                key_state[ALLEGRO_KEY_E]=0;
                Player->SetState(Type::IDLE);
                break;
            case ALLEGRO_KEY_SPACE:
                key_state[ALLEGRO_KEY_SPACE]=0;
                break;
        }
    }
    if(key_state[ALLEGRO_KEY_SPACE]){
        Player->SetState(Type::DODGE);
    }else if(key_state[ALLEGRO_KEY_W]){
        Player->SetState(Type::MOVE,UP);
    }else if(key_state[ALLEGRO_KEY_S])Player->SetState(Type::MOVE,DOWN);
    else if(key_state[ALLEGRO_KEY_A])Player->SetState(Type::MOVE,LEFT);
    else if(key_state[ALLEGRO_KEY_D])Player->SetState(Type::MOVE,RIGHT);
    else if(key_state[ALLEGRO_KEY_E]){
            Player->SetState(Type::ATTACK);
            //std::cout << "wtffffffffffffffff" << '\n';
    }
    if(redraw) {
        // update each object in game
        draw_running_map();
        instruction = game_update();
        // Re-draw map

        redraw = false;
        //std::cout << "are you in" << '\n';
        //std::cout << "hi" << '\n';
    }
    return instruction;
}

void
GameWindow::draw_running_map(){
    unsigned int i;
    if(!Player){
        //std::cout << "choose! you fool!\n";
        al_clear_to_color(al_map_rgb(100, 100, 100));
        draw_choose();
        //std::cout << "are you fucking running" << '\n';
    }
    else{
        //std::cout << "why the fuck is there no player" << '\n';
        //std::cout << Player->get_damage() << '\n';

        al_clear_to_color(al_map_rgb(100, 100, 100));
        al_draw_bitmap(background, 0, 0, 0);
        hud->Update(Player);
        hud->Draw();
        Player->Draw();
        for(i=0; i<monsterSet.size(); i++){
            monsterSet[i]->Draw();
        }
    }

    /*for(std::list<Tower*>::iterator it = towerSet.begin(); it != towerSet.end(); it++)
        (*it)->Draw();*/
    //al_draw_filled_rectangle(field_width, 0, window_width, window_height, al_map_rgb(100, 100, 100));


    al_flip_display();
}

void
GameWindow::draw_choose(){
    ui->Draw();
}
