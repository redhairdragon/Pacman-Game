#ifndef GRAPH_CONTROL_H
#define GRAPH_CONTROL_H
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>
#include "Creature_Graphic_Info.h"
#include <cmath>
#include <list>
#include <string>
using std::vector;
using std::list;
using std::string;
enum direction
{
    UP=0,DOWN=1,LEFT=2,RIGHT=3,NONE_Direction=4
};

class Graph_Control
{
public:
    Graph_Control();
    void run();


private:
    Game game;



    sf::RenderWindow window;
    sf::RectangleShape square[COL][ROW];
    //wall blocks

    Creature_Graphic pac_info;
    Creature_Graphic Smart1_info;
    Creature_Graphic Smart2_info;
    Creature_Graphic Smart3_info;
    Creature_Graphic Smart4_info;

    bool pause;
    bool freeze;
    bool AI;
    bool custom;
    bool L_Pressed;
    bool R_Pressed;

    sf::Texture General;
    sf::Clock g_clock;
    sf::Font font;
    sf::Time t;

    double move_speed;

    inline void SetWindow();
    //set window infos
    inline void SetInfo();
    //set ghosts infos
    inline void process_event();
    inline void draw();
    inline void update();

    inline void ResetGame();
    //reset everything

    inline bool CruiseTime(){return static_cast<int>(t.asSeconds()/7)%2!=0;}
    //return 1 if ghosts should cruise
    inline bool Move(Creature_Graphic& C, int Index_Num);
    //general move function for ghosts

    inline void Pacman_Animation(int Direction);
    //pacman animations
    inline bool Pacman_Move(int _d);
    //pacman moving function
    inline void Pacman_Move_Manipulation();
    //control pacman's moving pattern

    inline void Teleportation(Creature_Graphic& C,int Creature_Index);
    //teleport if C is in the portal
    //reset the game coord of C

    inline void Ghost_Animation(Creature_Graphic& Ghost, int Index_Num);
    //set ghost animations
    inline void Smart_Ghost_Move_Manipulation(Creature_Graphic& Ghost, int Index_Num);
    //control the ghost moving pattern for chasers
    inline void Smart_Ghost_Move_Manipulation2(Creature_Graphic& Ghost, int Index_Num);
    //control the ghost moving pattern for ambusers
    inline void CruiseMode(Creature_Graphic& Ghost, int Index_Num);
    //let ghost go to certain coords

    inline void Custom_Mapping(int x, int y, bool Left);
    //draw custom map

    inline int Pac_Ai();
    //return next direction of Pacman if it is AI
};

Graph_Control::Graph_Control()
{
    SetWindow();
    move_speed=5;
    if(!font.loadFromFile("Pipe_Dream_by_TRIFORCE89.ttf"))
        cout<<"not available.\n";
    SetInfo();
    pause=1;
    freeze=0;
    custom=0;
    L_Pressed=0;
    R_Pressed=0;
}
void Graph_Control::SetInfo()
{
    vector<sf::Texture> pac_V;
    pac_V.push_back(sf::Texture());
    pac_V.push_back(sf::Texture());
    pac_V.push_back(sf::Texture());
    pac_V.push_back(sf::Texture());

    General.loadFromFile("general.png");

    pac_info=Creature_Graphic((game.c[Pac_Index]->x-1)*20,(game.c[Pac_Index]->y-1)*20,NONE_Direction,pac_V);
    if(
        !pac_info.Texture[0].loadFromFile("PacManMovingUp.png")||
        !pac_info.Texture[1].loadFromFile("PacManMovingDown.png")||
        !pac_info.Texture[2].loadFromFile("PacmanSpriteLeft_48x16_3Frames.png")||
        !pac_info.Texture[3].loadFromFile("PacmanSpriteRight_48x16_3Frames.png"))
        exit(1);


    vector<sf::Texture> SM_1;
    SM_1.push_back(sf::Texture());

    Smart1_info=Creature_Graphic((game.c[SM_Index1]->x-1)*20,(game.c[SM_Index1]->y-1)*20,NONE_Direction,SM_1);
    if(!Smart1_info.Texture[0].loadFromFile("Blinky_RedGhost_128x16_8Frames.png"))
        exit(0);
    Smart1_info.Sprite.setTexture(Smart1_info.Texture[0]);
    Smart1_info.Cruise.push_back(sf::Vector2i(7,6));
    Smart1_info.Cruise.push_back(sf::Vector2i(7,2));
    Smart1_info.Cruise.push_back(sf::Vector2i(2,2));
    Smart1_info.Cruise.push_back(sf::Vector2i(2,6));

    vector<sf::Texture> SM_2;
    SM_2.push_back(sf::Texture());

    Smart2_info=Creature_Graphic((game.c[SM_Index2]->x-1)*20,(game.c[SM_Index2]->y-1)*20,NONE_Direction,SM_2);
    if(!Smart2_info.Texture[0].loadFromFile("Pinky_PinkGhost_128x16_8Frames.png"))
        exit(0);
    Smart2_info.Sprite.setTexture(Smart2_info.Texture[0]);
    Smart2_info.Cruise.push_back(sf::Vector2i(22,2));
    Smart2_info.Cruise.push_back(sf::Vector2i(27,2));
    Smart2_info.Cruise.push_back(sf::Vector2i(27,6));
    Smart2_info.Cruise.push_back(sf::Vector2i(22,6));

    vector<sf::Texture> SM_3;
    SM_3.push_back(sf::Texture());

    Smart3_info=Creature_Graphic((game.c[SM_Index3]->x-1)*20,(game.c[SM_Index3]->y-1)*20,NONE_Direction,SM_3);
    if(!Smart3_info.Texture[0].loadFromFile("Clyde_OrangeGhost_128x16_8Frames.png"))
        exit(0);
    Smart3_info.Sprite.setTexture(Smart3_info.Texture[0]);
    Smart3_info.Cruise.push_back(sf::Vector2i(7,21));
    Smart3_info.Cruise.push_back(sf::Vector2i(2,21));
    Smart3_info.Cruise.push_back(sf::Vector2i(4,27));
    Smart3_info.Cruise.push_back(sf::Vector2i(7,27));

    vector<sf::Texture> SM_4;
    SM_4.push_back(sf::Texture());

    Smart4_info=Creature_Graphic((game.c[SM_Index4]->x-1)*20,(game.c[SM_Index4]->y-1)*20,NONE_Direction,SM_4);
    if(!Smart4_info.Texture[0].loadFromFile("Inky_CyanGhost_128x16_8Frames.png"))
        exit(0);
    Smart4_info.Sprite.setTexture(Smart4_info.Texture[0]);
    Smart4_info.Cruise.push_back(sf::Vector2i(22,21));
    Smart4_info.Cruise.push_back(sf::Vector2i(27,21));
    Smart4_info.Cruise.push_back(sf::Vector2i(25,27));
    Smart4_info.Cruise.push_back(sf::Vector2i(22,27));

}

void Graph_Control::SetWindow()
{
    window.create(sf::VideoMode(560, 700), "Shen's Pacman");//NOT RESIZABLE ,sf::Style::Titlebar|sf::Style::Close
    window.setPosition(sf::Vector2i(0,0));//LEFT TOP CORNER
    window.setFramerateLimit(30);
}

void Graph_Control::run()
{
    while(window.isOpen())
    {
        process_event();
        if(!game.Check_Win())
        {
            update();
            draw();
            window.display();
            window.clear();
        }
    }
}

void Graph_Control::process_event()
{
    sf::Event Event;
    int temp=pac_info.Direction;

        while(window.pollEvent(Event))
        {
            switch (Event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if(Event.key.code==sf::Keyboard::C&&(pause||freeze))
                {
                    custom=!custom;
                    if(custom)
                    {
                        game=Game();
                        game.Map_Clear();
                    }
                    else
                    {
                        game=Game();
                    }
                    return;
                }
                if(Event.key.code==sf::Keyboard::R)
                    ResetGame();
                if(Event.key.code==sf::Keyboard::P)
                    freeze=!freeze;
                if(Event.key.code==sf::Keyboard::Escape)
                    window.close();
                if(Event.key.code==sf::Keyboard::Z)
                {
                    AI=!AI;
                }
                if(Event.key.code==sf::Keyboard::Up)
                {
                    temp=UP;
                }
                else if(Event.key.code==sf::Keyboard::Down)
                {
                    temp=DOWN;
                }
                else if(Event.key.code==sf::Keyboard::Left)
                {
                    temp=LEFT;
                }
                else if(Event.key.code==sf::Keyboard::Right)
                {
                    temp=RIGHT;
                }
                pac_info.NextDirection=temp;                
                if(pause==1)
                {
                pause=0;
                g_clock.restart();
                }
                break;
            case sf::Event::KeyReleased:
                if(Event.key.code==sf::Keyboard::A)
                {
                    Creature::Power_Time=!Creature::Power_Time;
                    game.Power_Time_clock.restart();
                }
                break;
            case sf::Event::MouseButtonPressed:
                if(custom)
                {
                    if (Event.mouseButton.button == sf::Mouse::Right)
                    {
                        R_Pressed=1;
                        L_Pressed=0;
                    }
                    if (Event.mouseButton.button == sf::Mouse::Left)
                    {
                        L_Pressed=1;
                        R_Pressed=0;
                    }
                    Custom_Mapping(Event.mouseButton.x,Event.mouseButton.y,L_Pressed);
                }
                break;
            case sf::Event::MouseMoved:
                if(custom)
                {
                    if(L_Pressed||R_Pressed)
                    {
                        Custom_Mapping(Event.mouseMove.x,Event.mouseMove.y,L_Pressed);
                    }
                }
                break;
            case sf::Event::MouseButtonReleased:
                if(custom)
                {
                    R_Pressed=0;
                    L_Pressed=0;
                }
                break;
            default:
                break;

            }
        }
}

void Graph_Control::update()
{
    if(!freeze)
    {
    if(AI)
        pause=0;
    if(!pause)
    {
        t=g_clock.getElapsedTime();
        Pacman_Move_Manipulation();
        if(t.asSeconds()>1)
            Smart_Ghost_Move_Manipulation(Smart1_info,SM_Index1);
        if(t.asSeconds()>3)
            Smart_Ghost_Move_Manipulation2(Smart2_info,SM_Index2);
        if(t.asSeconds()>5)
            Smart_Ghost_Move_Manipulation(Smart3_info,SM_Index3);
        if(t.asSeconds()>7)
            Smart_Ghost_Move_Manipulation(Smart4_info,SM_Index4);
        if(game.revive())
        {
            SetInfo();
            pause=1;
        }
        game.Update();
    }
    }
    Pacman_Animation(pac_info.Direction);
    Ghost_Animation(Smart1_info,SM_Index1);
    Ghost_Animation(Smart2_info,SM_Index2);
    Ghost_Animation(Smart3_info,SM_Index3);
    Ghost_Animation(Smart4_info,SM_Index4);

}

void Graph_Control::ResetGame()
{
    game.ResetCreatures();
    SetInfo();
}

void Graph_Control::draw()
{
    //back ground
    for(size_t i=0;i<COL;i++)
    {
        for(size_t j=0;j<ROW;j++)
        {
            square[i][j].setPosition(sf::Vector2f(i*20,j*20));
            if(game.Grid[i+1][j+1]==Wall)
            {
                square[i][j].setSize(sf::Vector2f(18,18));
                if(game.Check_Power_Time()==0)
                    square[i][j].setFillColor(sf::Color(255-5*i%255,255-5*j%255,255-(i+j)*2%255));
                else if (game.Check_Power_Time()==1)
                    square[i][j].setFillColor(sf::Color::Blue);
                else if (game.Check_Power_Time()==2)
                    square[i][j].setFillColor(sf::Color::White);
                window.draw(square[i][j]);
            }
            else if(game.Grid[i+1][j+1]==Pellet)
            {
                sf::CircleShape temp;
                temp.setPosition(sf::Vector2f(i*20+9,j*20+9));
                temp.setRadius(10);
                temp.setScale(1/10.0,1/10.0);
                temp.setFillColor(sf::Color::Yellow);
                window.draw(temp);
            }
            else if(game.Grid[i+1][j+1]==Power_Pellet)
            {
                sf::CircleShape temp;
                temp.setPosition(sf::Vector2f(i*20+6,j*20+6));
                temp.setRadius(10);
                temp.setScale(4/10.0,4/10.0);
                temp.setFillColor(sf::Color::Yellow);
                window.draw(temp);
            }
            else if(game.Grid[i+1][j+1]==Portal)
            {
                sf::RectangleShape P;
                P.setPosition(sf::Vector2f(i*20,j*20));
                P.setFillColor(sf::Color::Cyan);
                P.setSize(sf::Vector2f(20,20));
                window.draw(P);
            }
//            else if(game.Grid[i+1][j+1]==6)
//            {
//                sf::CircleShape temp;
//                temp.setPosition(sf::Vector2f(i*20+9,j*20+9));
//                temp.setRadius(10);
//                temp.setScale(7/10.0,7/10.0);
//                temp.setFillColor(sf::Color::Green);
//                window.draw(temp);
//            }
        }
    }


    //score text
    sf::Text score;
    score.setFont(font);
    score.setString("score:"+std::to_string((game.Score)));
    score.setCharacterSize(20);
    score.setColor(sf::Color::White);
    score.setPosition(sf::Vector2f(0,640));

    //live test
    sf::Text lives_text;
    lives_text.setFont(font);
    lives_text.setString("lives:"+std::to_string(game.Lives)+"  custom:C  restart:R  AI:Z  pause:p");
    lives_text.setPosition(sf::Vector2f(150,640));
    lives_text.setCharacterSize(20);

    window.draw(lives_text);
    window.draw(score);
    window.draw(Smart1_info.Sprite);
    window.draw(Smart2_info.Sprite);
    window.draw(Smart3_info.Sprite);
    window.draw(Smart4_info.Sprite);
    window.draw(pac_info.Sprite);

    //win text
    if(game.Check_Win())
    {
        sf::Text win_text;
        win_text.setFont(font);
        win_text.setPosition(sf::Vector2f(50,220));
        win_text.setCharacterSize(250);
        win_text.setString("WIN");
        win_text.setColor(sf::Color::Yellow);

        window.draw(win_text);
    }
}

void Graph_Control::Pacman_Move_Manipulation()
{
    if(!game.c[Pac_Index]->IsDead())
    {
        if(AI)
        {
            pac_info.NextDirection=Pac_Ai();
        }
        if(pac_info.NextDirection==pac_info.Direction)
            Pacman_Move(pac_info.Direction);
        else if(Pacman_Move(pac_info.NextDirection))
        {
            pac_info.Direction=pac_info.NextDirection;
        }
        else
        {
            Pacman_Move(pac_info.Direction);
        }
        pac_info.Sprite.setPosition(sf::Vector2f(pac_info.x,pac_info.y));
    }
}

void Graph_Control::Pacman_Animation(int Direction)
{
    if(game.c[Pac_Index]->IsDead())
        //die animation
    {
        if(pac_info.dead==0)
        {
            pac_info.Sprite_x=96;
            pac_info.Sprite_y=168;
            pac_info.dead=1;
        }
        pac_info.Sprite.setTexture(General);
        if(pac_info.Sprite_x!=380)
             pac_info.Sprite_x+=24;
        pac_info.Sprite.setTextureRect(sf::IntRect(pac_info.Sprite_x,pac_info.Sprite_y,24,24));
        pac_info.Sprite.setScale(sf::Vector2f(20/24.0,20/24.0));
        return;
    }

        switch (Direction)
        {
        case UP:
            pac_info.Sprite.setTexture(pac_info.Texture[0]);
            break;
        case DOWN:
            pac_info.Sprite.setTexture(pac_info.Texture[1]);
            break;
        case LEFT:
             pac_info.Sprite.setTexture(pac_info.Texture[2]);
            break;
        case RIGHT:
             pac_info.Sprite.setTexture(pac_info.Texture[3]);
            break;
        case NONE_Direction:
            pac_info.Sprite.setTexture(pac_info.Texture[3]);
        default:
            break;
        }
    pac_info.Sprite_y=0;
    if(pac_info.Sprite_x+16>=48)
        pac_info.Sprite_x=0;
    else
        pac_info.Sprite_x=pac_info.Sprite_x+16;
    pac_info.Sprite.setTextureRect(sf::IntRect(pac_info.Sprite_x,pac_info.Sprite_y,16,16));
    pac_info.Sprite.setScale(sf::Vector2f(20/16.0,20/16.0));
}

void Graph_Control::Ghost_Animation(Creature_Graphic& Ghost,int Index_Num)
{
    int Direction=Ghost.Direction;

    if(game.c[Index_Num]->Die==1)
        //ghost die animation
    {
        Ghost.Sprite_y=216;
        switch (Direction)
        {
        case UP:
            if(Ghost.Sprite_x<(192+6*24)||Ghost.Sprite_x>=(192+24*7))
                Ghost.Sprite_x=192+6*24;
            else
                Ghost.Sprite_x+=24;
            break;
        case DOWN:
            if(Ghost.Sprite_x<(192+48)||Ghost.Sprite_x>=(192+72))
                Ghost.Sprite_x=192+48;
            else
                Ghost.Sprite_x+=24;
            break;
        case LEFT:
            if(Ghost.Sprite_x<(192+4*24)||Ghost.Sprite_x>=(192+5*24))
                Ghost.Sprite_x=192+4*24;
            else
                Ghost.Sprite_x+=24;
            break;
        case RIGHT:
            if(Ghost.Sprite_x<192||Ghost.Sprite_x>=(192+24))
                Ghost.Sprite_x=192;
            else
                Ghost.Sprite_x+=24;
            break;
        case NONE_Direction:
            if(Ghost.Sprite_x<(192+6*24)||Ghost.Sprite_x>=(192+24*7))
                Ghost.Sprite_x=192+6*24;
            else
                Ghost.Sprite_x+=24;
            break;
        default:
            break;
        }
        Ghost.Sprite.setTexture(General);
        Ghost.Sprite.setTextureRect(sf::IntRect(Ghost.Sprite_x,Ghost.Sprite_y,24,24));
        Ghost.Sprite.setScale(sf::Vector2f(20/24.0,20/24.0));
        return;
    }
    else
    {
        if(Creature::Power_Time)
            //blue ghost animation
        {
            Ghost.Sprite_y=96;
            if(Ghost.Power_Time==0)
            {
                Ghost.Power_Time=1;
                Ghost.Sprite_x=192;
            }
            Ghost.Sprite_x+=24;
            if(Ghost.Sprite_x>(192+24))
                Ghost.Sprite_x=192;
            Ghost.Sprite.setTexture(General);
            Ghost.Sprite.setTextureRect(sf::IntRect(Ghost.Sprite_x,Ghost.Sprite_y,24,24));
            Ghost.Sprite.setScale(sf::Vector2f(20/24.0,20/24.0));
            return;
        }
        else
        {
            if(Ghost.Power_Time==1)
            {
                Ghost.Power_Time=0;
            }
        }
        {
        Ghost.Sprite_y=0;
        //normal ghosts animation
        switch (Direction)
        {
        case UP:
            if(Ghost.Sprite_x>=16)
                Ghost.Sprite_x=0;
            else
                Ghost.Sprite_x+=16;
            break;
        case DOWN:
            if(Ghost.Sprite_x<32||Ghost.Sprite_x>=48)
                Ghost.Sprite_x=32;
            else
                Ghost.Sprite_x+=16;
            break;
        case LEFT:
            if(Ghost.Sprite_x<64||Ghost.Sprite_x>=80)
                Ghost.Sprite_x=64;
            else
                Ghost.Sprite_x+=16;
            break;
        case RIGHT:
            if(Ghost.Sprite_x<96||Ghost.Sprite_x>=112)
                Ghost.Sprite_x=96;
            else
                Ghost.Sprite_x+=16;
            break;
        case NONE_Direction:
            if(Ghost.Sprite_x>=16)
                Ghost.Sprite_x=0;
            else
                Ghost.Sprite_x+=16;
            break;
        default:
            break;
        }
        Ghost.Sprite.setTexture(Ghost.Texture[0]);
        Ghost.Sprite.setTextureRect(sf::IntRect(Ghost.Sprite_x,Ghost.Sprite_y,16,16));
        Ghost.Sprite.setScale(sf::Vector2f(20/16.0,20/16.0));
        }
    }
}

bool Graph_Control::Pacman_Move(int _d)
{
    sf::Vector2i Direction;
    switch (_d) {
    case UP:
        Direction=sf::Vector2i(0,-1);
        break;
    case DOWN:
        Direction=sf::Vector2i(0,1);
        break;
    case LEFT:
        Direction=sf::Vector2i(-1,0);
        break;
    case RIGHT:
        Direction=sf::Vector2i(1,0);
        break;
    case NONE_Direction:
        Direction=sf::Vector2i(0,0);
        break;
    default:
        break;
    }
    bool temp=1;

    for(int i=0;i<move_speed;i++)
    {
        if(_d==UP&&(pac_info.x%20==0))
        {
            if(((pac_info.y-1)>=0)&&game.Grid[(pac_info.x)/20+1][(pac_info.y-1)/20+1]!=Wall)
            {
                pac_info.x=pac_info.x+Direction.x;
                pac_info.y=pac_info.y+Direction.y;
                temp= 1;
                continue;
            }
        }
        else if(_d==DOWN&&(pac_info.x%20==0))
        {
            if(game.Grid[pac_info.x/20+1][(pac_info.y)/20+2]!=Wall)
            {
                pac_info.x=pac_info.x+Direction.x;
                pac_info.y=pac_info.y+Direction.y;
                temp= 1;
                continue;
            }
        }
        else if(_d==LEFT&&(pac_info.y%20==0))
        {
            if((pac_info.x-1)>=0&&game.Grid[(pac_info.x-1)/20+1][pac_info.y/20+1]!=Wall)
            {
                pac_info.x=pac_info.x+Direction.x;
                pac_info.y=pac_info.y+Direction.y;
                temp= 1;
                continue;
            }
        }
        else if(_d==RIGHT&&(pac_info.y%20==0))
        {
            if(game.Grid[((pac_info.x)/20+2)][pac_info.y/20+1]!=Wall)
            {
                pac_info.x=pac_info.x+Direction.x;
                pac_info.y=pac_info.y+Direction.y;
                temp= 1;
                continue;
            }
        }
    temp=0;
    break;
    }
    Teleportation(pac_info,Pac_Index);

    return temp;
}

void Graph_Control::Teleportation(Creature_Graphic& C, int Creature_Index)
{
    size_t x=(C.x+10)/20+1;
    size_t y=(C.y+10)/20+1;

    if(game.Grid[x][y]==Portal)
    {
        int exit_direction=game.Portals.Exit_Direction(x,y);

        sf::Vector2i Direction;
        switch (exit_direction)
        {
        case UP:
            Direction=sf::Vector2i(0,-1);
            break;
        case DOWN:
            Direction=sf::Vector2i(0,1);
            break;
        case LEFT:
            Direction=sf::Vector2i(-1,0);
            break;
        case RIGHT:
            Direction=sf::Vector2i(1,0);
            break;
        case NONE_Direction:
            Direction=sf::Vector2i(0,0);
            break;
        default:
            break;
        }

        Coord temp(x,y);
        game.c[Creature_Index]->set_x(game.Portals.ExitPortal(temp).x+Direction.x);
        game.c[Creature_Index]->set_y(game.Portals.ExitPortal(temp).y+Direction.y);

        C.x=(game.c[Creature_Index]->x_coord()-1)*20;
        C.y=(game.c[Creature_Index]->y_coord()-1)*20;
        game.check_death();
    }
    else
    {
        game.c[Creature_Index]->x=(C.x+10)/20+1;
        game.c[Creature_Index]->y=(C.y+10)/20+1;
        game.check_death();
    }
}

void Graph_Control::Smart_Ghost_Move_Manipulation(Creature_Graphic& Ghost, int Index_Num)
{
    //release ghost
    if(game.c[Index_Num]->turn<(60/move_speed))
    {
        game.c[Index_Num]->turn++;
        Ghost.y-=move_speed;
        Ghost.Sprite.setPosition(sf::Vector2f(Ghost.x,Ghost.y));
        return;
    }

    bool turanable=game.CrossRoad(game.c[Index_Num]->x_coord(),game.c[Index_Num]->y_coord());    

    if(turanable&&Ghost.x%20==0&&Ghost.y%20==0)
    {
        size_t x=(Ghost.x+10)/20+1;
        size_t y=(Ghost.y+10)/20+1;

        if(game.c[Index_Num]->Die==1)//go to 14,12 to revive
        {
            Ghost.Direction=game.Next_Direction(x,y,14,12);
        }
        else if(Creature::Power_Time!=1)
        {
            if(CruiseTime()&&!custom)//go cruise mode
            {
                sf::Vector2i p_distance;
                 p_distance.x=abs(static_cast<int>(game.c[Pac_Index]->x_coord())-static_cast<int>(game.c[Index_Num]->x));
                 p_distance.y=abs(static_cast<int>(game.c[Pac_Index]->y_coord())-static_cast<int>(game.c[Index_Num]->y));
                if( p_distance.x<=3 && p_distance.y<=3)
                    Ghost.Direction=game.Next_Direction(x,y,game.c[Pac_Index]->x_coord(),game.c[Pac_Index]->y_coord());
                else
                {
                    sf::Vector2i temp=Ghost.Cruise[Ghost.Cruise_Index];
                    Ghost.Direction=game.Next_Direction(x,y,temp.x,temp.y);
                }
            }
            else//chase pacman
                Ghost.Direction=game.Next_Direction(x,y,game.c[Pac_Index]->x_coord(),game.c[Pac_Index]->y_coord());
        }
        else //run away from pacman
        {
            int _x=2,_y=2;
            game.PacMan_Free_Coord(_x,_y);
            Ghost.Direction=game.Next_Direction(x,y,_x,_y);
        }
        game.c[Index_Num]->x=(Ghost.x+10)/20+1;
        game.c[Index_Num]->y=(Ghost.y+10)/20+1;
    }


    if(Creature::Power_Time==0||game.c[Index_Num]->Die==1)
    {
        for(int i=0;i<move_speed-1;i++)//normal speed
            Move(Ghost,Index_Num);
    }
    else
    {
        for(int i=0;i<(move_speed-3);i++)// power time speed
            Move(Ghost,Index_Num);
    }

    if(CruiseTime()&&game.c[Index_Num]->IsDead()==0)//update cruise info
    {
        if(game.c[Index_Num]->x_coord()==Ghost.Cruise[Ghost.Cruise_Index].x&&(game.c[Index_Num]->y_coord()==Ghost.Cruise[Ghost.Cruise_Index].y))
        {
            Ghost.Cruise_Index++;
            if(Ghost.Cruise_Index==Ghost.Cruise.size())
                Ghost.Cruise_Index=0;
        }
    }
    Ghost.Sprite.setPosition(sf::Vector2f(Ghost.x,Ghost.y));
}

void Graph_Control::Smart_Ghost_Move_Manipulation2(Creature_Graphic& Ghost, int Index_Num)
{
    //release ghost
    if(game.c[Index_Num]->turn<(60/move_speed))
    {
        game.c[Index_Num]->turn++;
        Ghost.y-=move_speed;
        Ghost.Sprite.setPosition(sf::Vector2f(Ghost.x,Ghost.y));
        return;
    }
    bool turanable=game.CrossRoad(game.c[Index_Num]->x_coord(),game.c[Index_Num]->y_coord());

    if(turanable&&Ghost.x%20==0&&Ghost.y%20==0)
    {
        size_t x=(Ghost.x+10)/20+1;
        size_t y=(Ghost.y+10)/20+1;

        int _d=pac_info.Direction;
        sf::Vector2i Direction;
        switch (_d)
        {
        case UP:
        Direction=sf::Vector2i(0,-1);
        break;
        case DOWN:
        Direction=sf::Vector2i(0,1);
        break;
        case LEFT:
        Direction=sf::Vector2i(-1,0);
        break;
        case RIGHT:
        Direction=sf::Vector2i(1,0);
        break;
        case NONE_Direction:
        Direction=sf::Vector2i(0,0);
        break;
        default:
        break;
        }
        sf::Vector2i p_distance;

        p_distance.x=abs(static_cast<int>(game.c[Pac_Index]->x_coord())-static_cast<int>(game.c[Index_Num]->x));
        p_distance.y=abs(static_cast<int>(game.c[Pac_Index]->y_coord())-static_cast<int>(game.c[Index_Num]->y));

        size_t target_x=game.c[Pac_Index]->x_coord()+Direction.x*5;
        size_t target_y=game.c[Pac_Index]->y_coord()+Direction.y*5;

        if(game.c[Index_Num]->Die==1)//go to 14,12 to revive
        {
            Ghost.Direction=game.Next_Direction(x,y,14,12);
        }
        else if(Creature::Power_Time==1)//run away from pacman
        {
            int _x=2,_y=2;
            game.PacMan_Free_Coord(_x,_y);
            Ghost.Direction=game.Next_Direction(x,y,_x,_y);
        }
        else if(CruiseTime()&&!custom)//go to cruise mode
        {
            if( p_distance.x<=3&& p_distance.y<=3)//if pacman is close, go to chase
                Ghost.Direction=game.Next_Direction(x,y,game.c[Pac_Index]->x_coord(),game.c[Pac_Index]->y_coord());
            else
            {
                sf::Vector2i temp=Ghost.Cruise[Ghost.Cruise_Index];
                Ghost.Direction=game.Next_Direction(x,y,temp.x,temp.y);
            }
        }
        else if(p_distance.x<=2&&p_distance.y<=2)//if pacman is close, go to chase
        {
            int temp=game.Next_Direction(x,y,game.c[Pac_Index]->x_coord(),game.c[Pac_Index]->y_coord());
            if(temp!=6)
                Ghost.Direction=temp;
        }
        else if(target_x>1&&target_x<28&&
           target_y>1&&target_y<31&&
           game.Grid[target_x][target_y]!=Wall)
        {
            int temp=game.Next_Direction(x,y,target_x,target_y);//go to 2 blocks ahead pacman
            if(temp!=6)
                Ghost.Direction=temp;
            else
                Ghost.Direction=game.Next_Direction(x,y,game.c[Pac_Index]->x_coord(),game.c[Pac_Index]->y_coord());
        }
        else
        {
            int temp = game.Next_Direction(x,y,game.c[Pac_Index]->x_coord(),game.c[Pac_Index]->y_coord());
            if(temp!=6)
                Ghost.Direction=temp;
        }
    }

    if(Creature::Power_Time==0||game.c[Index_Num]->Die==1)
    {
        for(int i=0;i<move_speed-1;i++)
            Move(Ghost,Index_Num);
    }
    else
    {
        for(int i=0;i<(move_speed-3);i++)
            Move(Ghost,Index_Num);
    }

    if(CruiseTime()&&game.c[Index_Num]->IsDead()==0)
    //update cruise info
    {
        if(game.c[Index_Num]->x_coord()==Ghost.Cruise[Ghost.Cruise_Index].x&&(game.c[Index_Num]->y_coord()==Ghost.Cruise[Ghost.Cruise_Index].y))
        {
            Ghost.Cruise_Index++;
            if(Ghost.Cruise_Index==Ghost.Cruise.size())
                Ghost.Cruise_Index=0;
        }
    }
    Ghost.Sprite.setPosition(sf::Vector2f(Ghost.x,Ghost.y));
}

bool Graph_Control::Move(Creature_Graphic& C,int Index_Num)
{
    int _d=C.Direction;
    if(game.c[Index_Num]->Die==1&&C.dead==0)
    {
        C.dead=1;
        C.x=(C.x+10)/20*20;
        C.y=(C.y+10)/20*20;
    }
    if(game.c[Index_Num]->Die==0)
    {
        C.dead=0;
    }
    double speed=1;

    sf::Vector2i Direction;
    switch (_d)
    {
    case UP:
        Direction=sf::Vector2i(0,-1);
        break;
    case DOWN:
        Direction=sf::Vector2i(0,1);
        break;
    case LEFT:
        Direction=sf::Vector2i(-1,0);
        break;
    case RIGHT:
        Direction=sf::Vector2i(1,0);
        break;
    case NONE_Direction:
        Direction=sf::Vector2i(0,0);
        break;
    default:
        break;
    }

        if(_d==UP&&(C.x%20==0))
        {
            if(((C.y-1)>=0)&&game.Grid[(C.x)/20+1][(C.y-1)/20+1]!=Wall)
            {
                C.y=C.y+Direction.y*speed;
                Teleportation(C,Index_Num);
                return 1;
            }
        }
        else if(_d==DOWN&&(C.x%20==0))
        {
            if(game.Grid[C.x/20+1][(C.y)/20+2]!=Wall)
            {
                C.y=C.y+Direction.y*speed;
                Teleportation(C,Index_Num);
                return 1;
            }
        }
        else if(_d==LEFT&&(C.y%20==0))
        {
            if((C.x-1)>=0&&game.Grid[(C.x-1)/20+1][C.y/20+1]!=Wall)
            {
                C.x=C.x+Direction.x*speed;
                Teleportation(C,Index_Num);
                return 1;
            }
        }
        else if(_d==RIGHT&&(C.y%20==0))
        {
            if(game.Grid[((C.x)/20+2)][C.y/20+1]!=Wall)
            {
                C.x=C.x+Direction.x*speed;
                Teleportation(C,Index_Num);
                return 1;
            }
        }
        return 0;
}

int Graph_Control::Pac_Ai()
{
    bool avoid_ghost=!(Creature::Power_Time&&game.Power_Time_clock.getElapsedTime().asSeconds()<=2.75);

    //count ghosts nearby ,and find the nearest power pill
    int pacman_boundary[4];
    int radius=4;
    pacman_boundary[0]=game.c[Pac_Index]->x_coord()-radius;
    if(pacman_boundary[0]<2)
        pacman_boundary[0]=2;
    pacman_boundary[1]=game.c[Pac_Index]->x_coord()+radius;
    if(pacman_boundary[1]>27)
        pacman_boundary[1]=27;
    pacman_boundary[2]=game.c[Pac_Index]->y_coord()-radius;
    if(pacman_boundary[2]<2)
        pacman_boundary[2]=2;
    pacman_boundary[3]=game.c[Pac_Index]->y_coord()+radius;
    if(pacman_boundary[3]>30)
        pacman_boundary[3]=30;
    int count=0;
    int power_x=-1;
    int power_y=-1;

    for(int i=pacman_boundary[0];i<pacman_boundary[1];i++)
    {
        for(int j=pacman_boundary[2];j<pacman_boundary[3];j++)
        {
            for(int m=1;m<5;m++)
            {
                if(game.c[m]->x_coord()==i&&game.c[m]->y_coord()==j)
                    count++;
            }
            if(game.Grid[i][j]==Power_Pellet)
            {
                power_x=i;
                power_y=j;
            }
        }
    }

    if(count>=2&&power_x>0)//2 more ghosts nearby and pill found, then go for power pill
    {
        A_Star x(game.c[Pac_Index]->x_coord(),game.c[Pac_Index]->y_coord(),power_x,power_y,game.Grid,game.c,game.Portals,0);
        return x.Path_Finding();
    }

    //in the power time then go for eating ghosts
    if(Creature::Power_Time&&game.Power_Time_clock.getElapsedTime().asSeconds()<=3.5)
    {
        int search_boundary[4];
        //look for ghosts
        search_boundary[0]=game.c[Pac_Index]->x_coord()-5;
        if(search_boundary[0]<2)
            search_boundary[0]=2;
        search_boundary[1]=game.c[Pac_Index]->x_coord()+5;
        if(search_boundary[1]>27)
            search_boundary[1]=27;
        search_boundary[2]=game.c[Pac_Index]->y_coord()-5;
        if(search_boundary[2]<2)
            search_boundary[2]=2;
        search_boundary[3]=game.c[Pac_Index]->y_coord()+5;
        if(search_boundary[3]>30)
            search_boundary[3]=30;

        for(int i=search_boundary[0];i<=search_boundary[1];i++)
        {
            for(int j=search_boundary[2];j<=search_boundary[3];j++)
            {
                for(int m=1;m<5;m++)
                {
                    if(game.c[m]->x_coord()==i&&game.c[m]->y_coord()==j&&game.c[m]->Die==0)//ghosts found
                    {
                        if(j!=12)
                        {
                            A_Star x(game.c[Pac_Index]->x_coord(),game.c[Pac_Index]->y_coord(),i,j,game.Grid,game.c,game.Portals,0);
                            return x.Path_Finding();
                        }
                    }
                }
            }
        }
    }

    int d=10;
    //clear bottom left
    for(int i =2;i<=14;i++)
    {
        for (int j=16;j<=30;j++)
        {
            if(game.Grid[i][j]==Pellet)
            {
                A_Star x(game.c[Pac_Index]->x_coord(),game.c[Pac_Index]->y_coord(),i,j,game.Grid,game.c,game.Portals,avoid_ghost);
                d= x.Path_Finding();
                if (d!=10)
                    return d;
                else
                    continue;
            }
        }
    }
    //clear bottom right
    for(int i =15;i<=27;i++)
    {
        for (int j=16;j<=30;j++)
        {
            if(game.Grid[i][j]==Pellet)
            {
                A_Star x(game.c[Pac_Index]->x_coord(),game.c[Pac_Index]->y_coord(),i,j,game.Grid,game.c,game.Portals,avoid_ghost);
                d= x.Path_Finding();
                if (d!=10)
                    return d;
                else
                    continue;
            }
        }
    }
    //clear top right
    for(int i =27;i>=15;i--)
    {
        for (int j=14;j>=2;j--)
        {
            if(game.Grid[i][j]==Pellet)
            {
                A_Star x(game.c[Pac_Index]->x_coord(),game.c[Pac_Index]->y_coord(),i,j,game.Grid,game.c,game.Portals,avoid_ghost);
                d= x.Path_Finding();
                if (d!=10)
                    return d;
                else
                    continue;
            }
        }
    }
    //clear top left
    for(int i =14;i>=2;i--)
    {
        for (int j=14;j>=2;j--)
        {
            if(game.Grid[i][j]==Pellet)
            {
                A_Star x(game.c[Pac_Index]->x_coord(),game.c[Pac_Index]->y_coord(),i,j,game.Grid,game.c,game.Portals,avoid_ghost);
                d= x.Path_Finding();
                if (d!=10)
                    return d;
                else
                    continue;
            }
        }
    }

    //last pellet is ocuppied by the ghost
    if(d==10)
    {
        A_Star x(game.c[Pac_Index]->x_coord(),game.c[Pac_Index]->y_coord(),12,12,game.Grid,game.c,game.Portals,avoid_ghost);
        d= x.Path_Finding();
    }
}

void Graph_Control::Custom_Mapping(int x, int y, bool Left)
{
    int grid_x=x/20+1;
    int grid_y=y/20+1;
    if(grid_x<1||grid_x>28)
        return;
    if(grid_y<1||grid_y>30)
        return;
    if(Left)
    {
        if(game.Grid[grid_x][grid_y]!=Wall)
        {
            bool temp=1;
            for(int i=0;i<5;i++)
            {
                if(game.c[i]->x_coord()==grid_x&&game.c[i]->y_coord()==grid_y)
                {
                    temp=0;
                    break;
                }
            }
            if(temp)
                game.Grid[grid_x][grid_y]=Wall;
        }
    }
    else
    {
        if(game.Grid[grid_x][grid_y]!=0)
        {
            game.Grid[grid_x][grid_y]=0;
        }
    }
}

#endif // GRAPH_CONTROL_H

