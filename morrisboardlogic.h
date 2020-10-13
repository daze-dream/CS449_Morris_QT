#ifndef MORRISBOARDLOGIC_H
#define MORRISBOARDLOGIC_H
#include <map>
#include <set>
#include <vector>

using std::vector;
using std::map;

//Code contributed by Saurav

class MorrisBoardLogic
{
public:
    MorrisBoardLogic();



private:
    std::map<std::pair<char, char>, char> gameBoard; // prep for ASCII
    vector<int> p1moves;           //possible moves for player 1
    vector<int> p2moves;           //possible moves for player 2

    vector<int> occupied_cells;     //all the occupied cells
};

#endif // MORRISBOARDLOGIC_H
