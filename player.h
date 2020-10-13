#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

// Code contributed by Alec Ivy

using std::vector;


class Player
{
public:
    Player();
    Player(int id) {
            this->id = id;
            pieces = 9;
        }

    //getters
        int getId() {
            return id;
        }
        int getPieces() {
            return pieces;
        }
        vector<int> getPiecePos(){
            return piecePos;
        }


        //update methods
        //avaible piece to board
        void placePiece(int pos) {
            pieces--;
            piecePos.push_back(pos);
        }

        //take piece from board after mill
        void removePiece(int pos) {
            piecePos.erase(std::find(piecePos.begin(), piecePos.end(), pos)); //search vector for position and remove it
        }

        //moving pieces already on board
        void movePiece(int pos1, int pos2) { //piece from position1 to position 2
            removePiece(pos1);
            piecePos.push_back(pos2);
        }



private:
    int id = 0;
    int pieces = 0;
    //vector contains representation of players pieces on the board
    //24 possible piece locations, [1, 24] would represent a piece on first and last board location
    vector<int>piecePos;

};

#endif // PLAYER_H
