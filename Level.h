#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
#include <string>
#include <vector>
#include "global.h"


class LEVEL {
public:
    LEVEL(const int);
    ~LEVEL();

    void setLevel(const int);
    int getMonsterSpeed() { return MonsterSpeed; }
    int getLevel() { return level; }
    std::pair<int,int> MonsoterPos[Num_MonsterType];
    int MonsterNum[Num_MonsterType];


private:
    // current level number
    int level = 1;
    // maximum number of monster of a level
    int Monster_MAX = 50;
    // frequency of producing  monster
    int MonsterSpeed = 80;
};


#endif // LEVEL_H_INCLUDED
