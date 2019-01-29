#ifndef CREATURE_GRAPHIC_INFO_H
#define CREATURE_GRAPHIC_INFO_H
#include <SFML/Graphics.hpp>
#include <vector>
using std::vector;

struct Creature_Graphic
//graphic info of Creatures for class"Graph_cONTROL"
{
    Creature_Graphic();
    Creature_Graphic(int _x,int _y,int _d,vector<sf::Texture> _v);
    int x;
    int y;
    int Direction;
    int NextDirection;
    vector<sf::Texture> Texture;
    vector<sf::Vector2i> Cruise;
    //save coords for crusing

    size_t Cruise_Index;
    sf::Sprite Sprite;
    int Sprite_x;
    int Sprite_y;
    bool dead;
    bool Power_Time;
};

Creature_Graphic::Creature_Graphic()
{
    Power_Time=0;
    dead=0;
    NextDirection=4;
    Cruise_Index=0;

    Sprite_x=0;
    Sprite_y=0;
    Sprite.setPosition(x,y);
    Sprite.setScale(sf::Vector2f(20/16.0,20/16.0));
}

Creature_Graphic::Creature_Graphic(int _x, int _y, int _d, vector<sf::Texture> _v):x(_x),y(_y),Direction(_d),Texture(_v)
{
    Power_Time=0;
    dead=0;
    NextDirection=4;
    Cruise_Index=0;

    Sprite_x=0;
    Sprite_y=0;
    Sprite.setPosition(x,y);
    Sprite.setScale(sf::Vector2f(20/16.0,20/16.0));

}

#endif // CREATURE_GRAPHIC_INFO_H
