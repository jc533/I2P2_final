#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <iostream>

#define font_size 12
#define grid_width 40
#define grid_height 40

#define window_width 1600
#define window_height 900
#define field_width 1600
#define field_height 900

#define Num_ClassType 2
#define Num_MonsterType 5
#define Num_TowerType 5
#define NumOfGrid (field_width / grid_width) * (field_height / grid_height)

extern int TowerRadius[];
extern char TowerClass[][20];
extern int TowerWidth[];
extern int TowerHeight[];


const int axis_x[] = {-1, 1, 0, 0};
const int axis_y[] = {0, 0, -1, 1};
const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};
enum {ARCANE = 0, ARCHER, CANON, POISON, STORM};
enum {ASSASSIN = 0, ZOMBIE, WITCH, TURRET, BOMB};
enum {LEFT=0, RIGHT, UP, DOWN};
#endif // GLOBAL_H_INCLUDED
