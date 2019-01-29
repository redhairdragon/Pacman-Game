#ifndef PORTAL_H
#define PORTAL_H
#include <cstdlib>
#include <map>
#include <iostream>

struct Coord
{
    Coord(size_t _x=0,size_t _y=0):x(_x),y(_y){}
    size_t x;
    size_t y;
    friend bool operator <(const Coord& A,const Coord& B)
    {
        return ((A.x*100+A.y)<(B.x*100+B.y));
    }
    friend std::ostream& operator <<(std::ostream& out,const Coord& C)
    {
        out<<C.x<<','<<C.y;
        return out;
    }
};

struct Portal_Pair
//for saving 2 coords for portal pair
{
    Portal_Pair(Coord _A,Coord _B):A(_A),B(_B){}
    Coord A;
    Coord B;
    friend bool operator <(const Portal_Pair& L,const Portal_Pair& R)
    {
        return ((L.A.x*1000000+L.A.y*10000+L.B.x*100+L.B.y)<(R.A.x*1000000+R.A.y*10000+R.B.x*100+R.B.y));
    }
};

using std::pair;
class PortalList
//container save pairs of portals
{
public:
    PortalList(){}
    bool InsertPortal(size_t P1_x, size_t P1_y, int direction1, size_t P2_x, size_t P2_y, int direction2);
    bool InsertPortal(Coord A, int d1, Coord B, int d2);

    Coord ExitPortal(size_t Enter_x,size_t Enter_y);
    Coord ExitPortal(Coord Enter);

    int Exit_Direction(size_t Enter_x, size_t Enter_y);

    std::pair<int,int> ExitPosition(size_t Enter_x, size_t Enter_y);
private:
    std::map<Coord,Coord> m;//save portals
    std::map<Portal_Pair,int> d; //save directions of portal exits

};
bool PortalList::InsertPortal(size_t P1_x, size_t P1_y,int direction1, size_t P2_x, size_t P2_y,int direction2)
{
    size_t x=m.count(Coord(P1_x,P1_y));
    if(x==1)
        return 0;
    x=m.count(Coord(P2_x,P2_y));
    if(x==1)
        return 0;

    m.insert(std::pair<Coord,Coord>(Coord(P1_x,P1_y),Coord(P2_x,P2_y)));
    d.insert(std::pair<Portal_Pair,int>(Portal_Pair(Coord(P1_x,P1_y),Coord(P2_x,P2_y)),direction1));
            //d1 P2 out direction
    m.insert(std::pair<Coord,Coord>(Coord(P2_x,P2_y),Coord(P1_x,P1_y)));
    d.insert(std::pair<Portal_Pair,int>(Portal_Pair(Coord(P2_x,P2_y),Coord(P1_x,P1_y)),direction2));
    return 1;
}

bool PortalList::InsertPortal(Coord A,int d1, Coord B,int d2)
{
    return InsertPortal(A.x,A.y,d1,B.x,B.y,d2);

}
Coord PortalList::ExitPortal(Coord Enter)
{
    return ExitPortal(Enter.x,Enter.y);
}

Coord PortalList::ExitPortal(size_t Enter_x, size_t Enter_y)
{
    std::map<Coord,Coord>::iterator x;
    x=m.find(Coord(Enter_x,Enter_y));
    if(x!=m.end())
    {
        std::pair<Coord,Coord> r=*x;
        return m[r.first];
    }
    else
        return Coord(999,999);
}

int PortalList::Exit_Direction(size_t Enter_x, size_t Enter_y)
{
    std::map<Coord,Coord>::iterator x;
    x=m.find(Coord(Enter_x,Enter_y));
    if(x!=m.end())
    {
        std::pair<Coord,Coord> r=*x;
        std::map<Portal_Pair,int>::iterator it=d.find( Portal_Pair(Coord(Enter_x,Enter_y),m[r.first]));
        std::pair<Portal_Pair,int> return_v=*it;

        return return_v.second;
    }
    else
        return 5;
}

std::pair<int, int> PortalList::ExitPosition(size_t Enter_x, size_t Enter_y)
{
    Coord c=ExitPortal(Enter_x,Enter_y);
    int d=Exit_Direction(Enter_x,Enter_y);
    std::pair<int,int> d_v;
    switch (d)
    {
    case 0:
        d_v=std::pair<int,int>(0,-1);
        break;
    case 1:
        d_v=std::pair<int,int>(0,1);
        break;
    case 2:
        d_v=std::pair<int,int>(-1,0);
        break;
    case 3:
        d_v=std::pair<int,int>(1,0);
        break;
    default:
        break;
    }
    return std::pair<int,int>(c.x+d_v.first,c.y+d_v.second);
}

#endif // PORTAL_H
