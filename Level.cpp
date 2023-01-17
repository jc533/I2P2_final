#include "Level.h"
#include <iostream>

LEVEL::LEVEL(const int level) {
    char buffer[50];

    setLevel(level);
}

LEVEL::~LEVEL(){}

void
LEVEL::setLevel(const int level)
{
    char buffer[50];
    FILE *file;

    sprintf(buffer, "LEVEL%d.txt", level);
    file = fopen(buffer, "r");

    this->level = level;

    fscanf(file, "%s", buffer);
    Monster_MAX = atoi(buffer);

    for(int i=0; i < Num_MonsterType; i++){
        fscanf(file, "%s", buffer);
        MonsterNum[i] = atoi(buffer);
    }
    for(int i=0; i < Num_MonsterType; i++){
        std::pair<int,int> tmp;
        fscanf(file, "%s", buffer);
        tmp.first = atoi(buffer);
        fscanf(file, "%s", buffer);
        tmp.second = atoi(buffer);
        std::cout << "tmp " << tmp.first <<' ' << tmp.second << '\n';
        MonsterPos[i] = tmp;
    }

    fclose(file);
}
