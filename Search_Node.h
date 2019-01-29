#ifndef SEARCH_NODE_H
#define SEARCH_NODE_H
//node class for a star searching
struct SearchNode
{
    SearchNode(int _x=0, int _y=0);
    int x;
    int y;
    int G_value;
    //the value for recording the cost to the current node
    int H_value;
    //the value for estimating the cost between the current node and the destination
    int F_value;
    //sum of G and H

    bool is_visited;
    SearchNode* parent;
    //point to the parent node

    friend int Manhattan(SearchNode* A,SearchNode* B)
    //return the sum of the vertical and horizontal distance between two nodes
    //H value
    {
        return abs(A->x-B->x)+abs(A->y-B->y);
    }

    friend bool operator <(const SearchNode& L,const SearchNode& R)
    //compare nodes by their F value
    {
        return (L.F_value)>(R.F_value);
    }
};

SearchNode::SearchNode(int _x, int _y)
{
    x=_x;
    y=_y;
    G_value=0;
    H_value=0;
    F_value=INT_MAX;
    is_visited=0;
    parent=NULL;
}

bool Check_Coords(SearchNode n)
//check if the coord in node N is legitimate
{
    if(n.x<0||n.y<0||n.y>32||n.x>29)
        return 0;
    else
        return 1;
}

#endif // SEARCH_NODE_H
