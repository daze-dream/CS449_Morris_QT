#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <map>
#include "boardgui.h"
#include "piecegui.h"
#include "morrisboardlogic.h"


void drawBoard(QGraphicsScene &scene);
void drawPieces(QGraphicsScene &scene, std::map<std::pair<char, char>, char> &gameBoard);
void redrawBoard(std::pair<char, char> from, std::pair<char, char> to, QGraphicsScene * scene);



namespace CF{
    bool editedCustomBoardFlag = false; //Has a custom board been created?
    bool resetFlag = false; //Reset the game
    bool refreshFlag = false; //Refresh the scene

    bool whiteAIFlag = false; //Is white AI-controlled?
    bool blackAIFlag = false; //Is black AI-controlled?
    bool playerMovingFlag = false; //Avoids interrupting
}

namespace CV{
    std::map<std::pair<char, char>, char> gameBoard;

    int playerTurn = 1; //White goes first
    int gameStatus = 0; //Displays in top right hand corner

    QString movesListString = QString("White\tBlack\n"); //keeps a list of the moves taken
    QString movesListString2 = QString("White\tBlack\n"); //for the second column if the first fills up
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene *scene = new QGraphicsScene();
    drawBoard(*scene);
    drawPieces(*scene, CV::gameBoard);

    QGraphicsView *view = new QGraphicsView(scene);

    view->show();
    return a.exec();
}

void drawBoard(QGraphicsScene &scene) // we have a board layout for checkers. need to modify for 9MM
{
    int xOffset = 10;
    int yOffset = 85;
    //Prints the black squares of the board
       for (char y = '1'; y <= '8'; y++){
           for (char x = 'a'; x <= 'h'; x++){
               if ((((y - 49) % 2) == 0) == (((x - 97) % 2) == 0)){  //XNOR to help with the diagonalness of the board
                   QGraphicsItem *boardSquareItem = new BoardGUI((x-97)*75 + 75, 525-(y-49)*75 + yOffset, std::make_pair(x, y));
                   scene.addItem(boardSquareItem);
               }
           }
       }

       scene.addRect(75, yOffset, 600, 600);

}

void drawPieces(QGraphicsScene &scene, std::map<std::pair<char, char>, char> &gameBoard)
{
    int yOffset = 85;
    QColor currColor = Qt::black;
    for(int i = 0; i < 9; i++)
    {
        QGraphicsItem *piece = new PieceGUI(-30, (80* i) + yOffset, currColor,std::make_pair(0,0), 1);
        scene.addItem(piece);
        char ipiece = gameBoard[std::make_pair(0,0)];
    }
    currColor = Qt::white;
    for(int i = 0; i < 9; i++)
    {
        QGraphicsItem *piece = new PieceGUI(750, (80* i) + yOffset, currColor,std::make_pair(0,0), 1);
        scene.addItem(piece);
    }
}


void redrawBoard(std::pair<char, char> from, std::pair<char, char> to, QGraphicsScene * scene)
{
    scene->clear();
    drawBoard(*scene);
    //drawPieces(*scene, CV::gameBoard);
}















