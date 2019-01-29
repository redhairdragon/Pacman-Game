#ifndef A_STAR_H
#define A_STAR_H
#include <cstdlib>
#include <queue>
#include <iostream>
#include <stack>
#include "Game.h"
#include <cmath>
#include "Search_Node.h"
using namespace std;

//class for A_star algorithom
class A_Star
{
public:
    A_Star(size_t _start_x, size_t _start_y, size_t _end_x, size_t _end_y, int **_Grid, Creature* _ghosts[], const PortalList &_PL, bool pacman);
    int Path_Finding();
    //return a integer which represents the next direction

private:
    SearchNode* start;
    SearchNode* end;

    static int direction[4][2];//4 directions

    int** Grid;
    SearchNode* nodes[30][33];
    std::priority_queue<SearchNode> q;//list to check
    bool pac_ai;//path finding for pacman
    Creature* ghosts[5];
    PortalList PL;//portals
};

int A_Star::direction[4][2]={{0,1},{0,-1},{-1,0},{1,0}};

A_Star::A_Star(size_t _start_x, size_t _start_y, size_t _end_x, size_t _end_y, int **_Grid, Creature *_ghosts[],const PortalList& _PL, bool pacman)
{
    PL=_PL;
    for(int i=0;i<5;i++)
        ghosts[i]=_ghosts[i];
    pac_ai=pacman;
    Grid=_Grid;
    for(int i=0;i<30;i++)
    {
        for(int j=0;j<33;j++)
        {
            nodes[i][j]=new SearchNode(i,j);
        }
    }//initialize the Searchnodes

    start=nodes[_start_x][_start_y];
    end=nodes[_end_x][_end_y];

    start->H_value=Manhattan(start,end);
    end->H_value=Manhattan(end,end);
}

int A_Star::Path_Finding()
{
    if(pac_ai)
    //set nodes if it is for pac man AI
    {
        int temp=150000000;
        for(int m=1;m<5;m++)
        {
            if(ghosts[m]->IsDead()!=1)
            {
                int radius=2;
                int ghost_x=ghosts[m]->x_coord();
                int ghost_y=ghosts[m]->y_coord();
                int dis_x=abs(ghost_x-ghosts[0]->x_coord())*300;
                int dis_y=abs(ghost_x-ghosts[0]->y_coord())*300;
                int danger_boundary[4];

                danger_boundary[0]=ghost_x-radius;
                if(danger_boundary[0]<2)
                    danger_boundary[0]=2;
                danger_boundary[1]=ghost_x+radius;
                if(danger_boundary[1]>27)
                    danger_boundary[1]=27;
                danger_boundary[2]=ghost_y-radius;
                if(danger_boundary[2]<2)
                    danger_boundary[2]=2;
                danger_boundary[3]=ghost_y+radius;
                if(danger_boundary[3]>30)
                    danger_boundary[3]=30;

                for(int i=danger_boundary[0];i<=danger_boundary[1];i++)
                {
                    for(int j=danger_boundary[2];j<=danger_boundary[3];j++)
                    {
                        int small=abs(i-ghost_x);
                        if(abs(j-ghost_y)>small)
                        {
                            small=abs(j-ghost_y);
                        }
                        nodes[i][j]->G_value+=(temp-small*200-dis_x-dis_y);
                        if(end->x==i&&end->y==j)
                            return 10;
                    }
                }
            }
        }
        for(int i=2;i<28;i++)
        {
            for(int j=2;j<=30;j++)
            {
                if(Grid[i][j]==1)
                    nodes[i][j]->G_value-=5;
                else if(Grid[i][j]==2)
                    nodes[i][j]->G_value+=100;
            }
        }
    }

    try
    {
    if(Grid[start->x][start->y]==3)
        throw 1;
    SearchNode current=*start;
    q.push(*start);
    while(!q.empty())
    //check openlist
    {
        current=q.top();
        q.pop();
        if( nodes[current.x][current.y]->is_visited==1)
        {
            continue;
        }
        nodes[current.x][current.y]->is_visited=1;

        if(current.x==end->x&&current.y==end->y)
        {
            break;
        }
        for(int i=0;i<4;i++)
        //check adjacent blocks
        {
            SearchNode* adj=nodes[current.x+direction[i][0]][current.y+direction[i][1]];
            if(Grid[adj->x][adj->y]==3||adj->is_visited==1)
                continue;
            else if(Check_Coords(*adj)&&adj->is_visited==0)
            {
                adj->G_value+=current.G_value+1;
                adj->H_value=Manhattan(adj,end);
                if((adj->G_value+adj->H_value)<adj->F_value)
                {
                    adj->F_value=adj->G_value+adj->H_value;
                    adj->parent=nodes[current.x][current.y];
                    q.push(*adj);
                }
                else
                {
                    continue;
                }
            }
        }
    }
    }
    catch (int e)
    {
    }

    if(end->parent==NULL)//no path
    {
    }
    else
    {
        SearchNode* walker=end;
        stack<SearchNode> path;
        while(walker!=NULL)
        //get the route
        {
            path.push(*walker);
            walker=walker->parent;
        }
        path.pop();
        int x=path.top().x,y=path.top().y;
        if(Grid[x][y]!=4)
        {
            //calculate direction
            if(x-start->x==0&&y-start->y==-1)
                return 0;
            else if(x-start->x==0&&y-start->y==1)
                return 1;
            else if(x-start->x==-1&&y-start->y==0)
                return 2;
            else if(x-start->x==1&&y-start->y==0)
                return 3;
            else if(x-start->x==0&&y-start->y==0)
                return 4;
            else
                return 5;
        }
    }
    return 6;//no path
}

#endif // A_STAR_H
