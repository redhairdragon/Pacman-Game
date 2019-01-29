#ifndef CREATURE_H
#define CREATURE_H
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

class Creature
//save creature information for game class
{
    friend class Graph_Control;
    friend class Game;
public:
    Creature(){cout<<"Should not be called.\n";}
    Creature(size_t _x,size_t _y):x(_x),y(_y),Die(0),turn(0){}
    ~Creature(){}

    void SetDead(){Die=1;}
    int x_coord(){return x;}
    int y_coord(){return y;}

    void set_x(size_t _x){x=_x;}
    void set_y(size_t _y){y=_y;}

    bool IsDead(){return Die;}
    static void SetBlue(bool flag){Power_Time=flag;}
protected:
    int x;
    int y;
    static bool Power_Time;
    bool Die;
    int turn;
};

bool Creature::Power_Time=0;

#endif // CREATURE_H
