#ifndef GAME_H
#define GAME_H
#include<cstdlib>
#include <iostream>
#include <string>
#include <Creature.h>
#include "Graph_Control.h"
#include "Portal.h"
#include "A_star.h"
using std::cout;
using std::endl;
const size_t ROW=31;
const size_t COL=28;

enum{
    None=0,Pellet=1,Power_Pellet=2,Wall=3,Portal=4,
    Pac_Index=0,SM_Index4=4,SM_Index3=3,SM_Index1=1,SM_Index2=2
};


class Game
{
    friend class Graph_Control;
public:
    Game();
    Game(const Game &_Game);
    Game& operator =(const Game &_Game);

    void Map_Clear();
    //set a map for customming

    void Update();
    //should be called by SFML class for each frame

    bool CrossRoad(int x, int y);
    //check if the x,y is at intersection

    void check_death();

    int Next_Direction(size_t from_x,size_t from_y,size_t to_x,size_t to_y)
    {
        A_Star searching(from_x,from_y,to_x,to_y,Grid,c,Portals,0);
        return searching.Path_Finding();
    }

    bool revive();
    // revive the pacman

    void PacMan_Free_Coord(int &x,int& y);
    //set x,y to an area without pacman

    bool Check_Win();

    int Check_Power_Time();
    //return an int which indicates the state of Powertime
    //if 1, it is power time
    //if 2, power time  is going to end
    //if 0, not power time

    void ResetCreatures();

    ~Game();

private:
    Creature* c[5];
    int** Grid;
    int Lives;
    unsigned int Score;
    PortalList Portals;

    sf::Clock Power_Time_clock;
};


Game::Game(const Game & _Game)
{
    Lives=3;
    Score=0;
    Grid=new int*[COL+2];

    for(size_t i=0;i<COL+2;i++)
    {
        Grid[i]=new int[ROW+2];
    }
    for(size_t i=0;i<ROW+2;i++)
    {
        for(size_t j=0;j<COL+2;j++)
        {
            Grid[j][i]=_Game.Grid[j][i];
        }
    }

    //create creatures
    c[Pac_Index]=new Creature(15,24);//player
    c[SM_Index1]=new Creature(16,15);
    c[SM_Index2]=new Creature(15,15);
    c[SM_Index3]=new Creature(14,15);
    c[SM_Index4]=new Creature(13,15);
    Portals.InsertPortal(1,15,2,28,15,3);
}

Game& Game::operator =(const Game &_Game)
{
    Lives=3;
    Score=0;
    Grid=new int*[COL+2];

    for(size_t i=0;i<COL+2;i++)
    {
        Grid[i]=new int[ROW+2];
    }
    for(size_t i=0;i<ROW+2;i++)
    {
        for(size_t j=0;j<COL+2;j++)
        {
            Grid[j][i]=_Game.Grid[j][i];
        }
    }

    c[Pac_Index]=new Creature(15,24);//player
    c[SM_Index1]=new Creature(16,15);
    c[SM_Index2]=new Creature(15,15);
    c[SM_Index3]=new Creature(14,15);
    c[SM_Index4]=new Creature(13,15);
    Portals.InsertPortal(1,15,2,28,15,3);
    return *this;
}

bool Game::CrossRoad(int x,int y)
{
    bool wall[4];
    int count=0;
    std::vector<sf::Vector2i> directions;
    directions.push_back(sf::Vector2i(0,-1));
    directions.push_back(sf::Vector2i(0,1));
    directions.push_back(sf::Vector2i(-1,0));
    directions.push_back(sf::Vector2i(1,0));

    for(int i=0;i<4;i++)
    {
        wall[i]=1;
        if(Grid[x+directions[i].x][y+directions[i].y]!=Wall)
        {
            wall[i]=0;
            count++;
        }
    }
    if(count>=3)
        return 1;
    else if (count ==2)
    {
        if(wall[0]==0&&wall[1]==0)
            return 0;
        if(wall[2]==0&&wall[3]==0)
            return 0;
        else
            return 1;
    }
    else
    {
        return 0;
    }
}

void Game::check_death()
{
    if(Creature::Power_Time==0)
    {
        for(int i=1;i<5;i++)
        {
            if(c[Pac_Index]->x_coord()==c[i]->x_coord()&&c[Pac_Index]->y_coord()==c[i]->y_coord()&&c[i]->Die!=1&&c[Pac_Index]->IsDead()==0)
            {
                c[Pac_Index]->Die=1;
                Lives--;
            }
        }
    }
    else
    {
        for(int i=1;i<5;i++)
        {
            if(c[Pac_Index]->x_coord()==c[i]->x_coord()&&c[Pac_Index]->y_coord()==c[i]->y_coord()&&c[i]->Die==0)
            {
                c[i]->Die=1;
                Score+=500;
            }
        }
    }
    for(int i=1;i<5;i++)
    {
        if(c[i]->x_coord()==14&&c[i]->y_coord()==12&&c[i]->Die==1)
       {
           c[i]->Die=0;
       }
    }
}

void Game::Map_Clear()
{
    std::string map[ROW];
    {
    map[0]= "3333333333333333333333333333";
    map[1]= "3111111111111111111111111113";
    map[2]= "3121111111111111111111112113";
    map[3]= "3111111111111111111111111113";
    map[4]= "3111111111111111111111111113";
    map[5]= "3111111111111111111111111113";
    map[6]= "3111111111111111111111111113";
    map[7]= "3111111111111111111111111113";
    map[8]= "3111111111111111111111111113";
    map[9]= "3111111111111111111111111113";
    map[10]="3111111111111111111111111113";
    map[11]="3111111111111111111111111113";
    map[12]="3111111110333333330111111113";
    map[13]="3111111110300000030111111113";
    map[14]="3000000000300000030000000003";
    map[15]="3111111110300000030111111113";
    map[16]="3111111110333333330111111113";
    map[17]="3111111111111111111111111113";
    map[18]="3111111111111111111111111113";
    map[19]="3111111111111111111111111113";
    map[20]="3111111111111111111111111113";
    map[21]="3111111111111111111111111113";
    map[22]="3111111111111111111111111113";
    map[23]="3111111111111111111111111113";
    map[24]="3111111111111111111111111113";
    map[25]="3111111111111111111111111113";
    map[26]="3111111111111111111111111113";
    map[27]="3111111111111111111111111113";
    map[28]="3112111111111111111111112113";
    map[29]="3111111111111111111111111113";
    map[30]="3333333333333333333333333333";
    }
    for(size_t i=0;i<ROW;i++)
    {
        for(size_t j=0;j<COL;j++)
        {
            Grid[j+1][i+1]=map[i].at(j)-'0';
        }
    }

}

Game::Game()
{
    Lives=3;
    Score=0;
    Grid=new int*[COL+2];

    for(size_t i=0;i<COL+2;i++)
    {
        Grid[i]=new int[ROW+2];
    }
    for(size_t i=0;i<(ROW+2);i++)
    {
        Grid[0][i]=Wall;
        Grid[COL+1][i]=Wall;
    }
    for(size_t i=0;i<(COL+2);i++)
    {
        Grid[i][0]=Wall;
        Grid[i][ROW+1]=Wall;
    }


    std::string map[ROW];
    {
    map[0]= "3333333333333333333333333333";
    map[1]= "3111111111111331111111111113";
    map[2]= "3133331333331331333331333313";
    map[3]= "3233331333331331333331333323";
    map[4]= "3133331333331331333331333313";
    map[5]= "3111111111111111111111111113";
    map[6]= "3133331331333333331331333313";
    map[7]= "3133331331333333331331333313";
    map[8]= "3111111331111331111331111113";
    map[9]= "3333331333330330333331333333";
    map[10]="3333331333330330333331333333";
    map[11]="3333331330000000000331333333";
    map[12]="3333331330333333330331333333";
    map[13]="3333331330300000030331333333";
    map[14]="4000000000300000030000000004";
    map[15]="3333331330300000030331333333";
    map[16]="3333331330333333330331333333";
    map[17]="3333331330000000000331333333";
    map[18]="3333331330333333330331333333";
    map[19]="3333331330333333330331333333";
    map[20]="3111111111111331111111111113";
    map[21]="3133331333331331333331333313";
    map[22]="3133331333331331333331333313";
    map[23]="3211331111111111111111331123";
    map[24]="3331331331333333331331331333";
    map[25]="3331331331333333331331331333";
    map[26]="3111111331111331111331111113";
    map[27]="3133333333331331333333333313";
    map[28]="3133333333331331333333333313";
    map[29]="3111111111111111111111111113";
    map[30]="3333333333333333333333333333";
    }
    for(size_t i=0;i<ROW;i++)
    {
        for(size_t j=0;j<COL;j++)
        {
            Grid[j+1][i+1]=map[i].at(j)-'0';
        }
    }

    c[Pac_Index]=new Creature(15,24);//player
    c[SM_Index1]=new Creature(16,15);
    c[SM_Index2]=new Creature(15,15);
    c[SM_Index3]=new Creature(14,15);
    c[SM_Index4]=new Creature(13,15);

    Portals.InsertPortal(1,15,2,28,15,3);
}

void Game::Update()
{
    check_death();
    if (Grid[c[Pac_Index]->x_coord()][c[Pac_Index]->y_coord()]==Pellet)
    {//eat pellet
        Score+=10;
        Grid[c[Pac_Index]->x_coord()][c[Pac_Index]->y_coord()]=None;
    }
    else if (Grid[c[Pac_Index]->x_coord()][c[Pac_Index]->y_coord()]==Power_Pellet)
    {//eat power pellet
        Creature::SetBlue(1);
        Score+=100;
        Grid[c[Pac_Index]->x_coord()][c[Pac_Index]->y_coord()]=None;
        Power_Time_clock.restart();
    }

    if(Creature::Power_Time==1)
    {//check powertime
        if(Power_Time_clock.getElapsedTime().asSeconds()>=4)
        {
            Creature::SetBlue(0);
        }
    }

}

Game::~Game()
{
    for(size_t i=0;i<COL+2;i++)
    {
        delete[] Grid[i];
    }
    delete[] Grid;
    for(size_t i=0;i<5;i++)
        delete c[i];
}

void Game:: PacMan_Free_Coord(int &x,int& y)
{
    if(c[Pac_Index]->x_coord()<14)
    {
        if(c[Pac_Index]->y_coord()<14)
        {
            x=27;y=30;
        }
        else
        {
            x=27;y=2;
        }
    }
    else
    {
        if(c[Pac_Index]->y_coord()<14)
        {
            x=2;y=30;
        }
        else
        {
            x=2;y=2;
        }
    }
}

int Game::Check_Power_Time()
{
    if(Creature::Power_Time)
    {
        float t=Power_Time_clock.getElapsedTime().asMilliseconds();
        if((t>3250&&t<3500)||((t>3750&&t<4000)))
        {
            return 2;
        }
        else
            return 1;
    }
    else
        return 0;
}

void Game::ResetCreatures()
{
    Lives=3;
    Score=0;
    c[Pac_Index]=new Creature(15,24);//player
    c[SM_Index1]=new Creature(16,15);
    c[SM_Index2]=new Creature(15,15);
    c[SM_Index3]=new Creature(14,15);
    c[SM_Index4]=new Creature(13,15);
}


bool Game::Check_Win()
{
    bool win=1;
    for(size_t i=0;i<ROW+2;i++)
    {
        for(size_t j=0;j<COL+2;j++)
        {
            if(Grid[j][i]==Pellet)
            {
                win=0;
                break;
            }
        }
    }
    return win;

}


bool Game::revive()
{
    if(c[Pac_Index]->Die==1&&Lives>=1)
    {
        c[Pac_Index]=new Creature(15,24);//player
        c[SM_Index1]=new Creature(16,15);
        c[SM_Index2]=new Creature(15,15);
        c[SM_Index3]=new Creature(14,15);
        c[SM_Index4]=new Creature(13,15);
        return 1;
    }
    else
         return 0;
}

#endif // GAME_H
