#ifndef MORRISBOARDLOGIC_H
#define MORRISBOARDLOGIC_H
#include <map>
#include <set>

class MorrisBoardLogic
{
public:
    MorrisBoardLogic();
private:
    std::map<std::pair<char, char>, char> gameBoard;
};

#endif // MORRISBOARDLOGIC_H
