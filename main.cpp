#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <map>
#include "boardgui.h"
#include "piecegui.h"
#include "morrisboardlogic.h"
#include <QGraphicsRectItem>
#include <QRect>


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
    int xOffset = 30;
    int yOffset = 50;

    int asciiNumOffset = 48, asciiCharOffset = 97;

    // These are virtual models of each of the "rings" in 9MM board. Rings adapted from CPU architecture
    QRect *ring3M = new QRect(xOffset, yOffset, 800, 800); //outer ring of board
    QRect *ring2M = new QRect(xOffset+100, yOffset+100, 600, 600); // middle ring of board
    QRect *ring1M = new QRect(xOffset+200, yOffset+200, 400, 400); // inner ring of board

    // these are the actual drawn rings on screen
    QGraphicsRectItem *ring3 = new QGraphicsRectItem(xOffset, yOffset, 800, 800, nullptr);
    scene.addItem(ring3);
    QGraphicsRectItem *ring2 = new QGraphicsRectItem(xOffset+100, yOffset+100, 600, 600, nullptr);
    scene.addItem(ring2);
    QGraphicsRectItem *ring1 = new QGraphicsRectItem(xOffset+200, yOffset+200, 400, 400, nullptr);
    scene.addItem(ring1);

    // generating places on the board based on these rings
    //      doing a translation from ASCII does allow us to store it as a coord
    for(int i = 0; i <3; i++) // ring 3
    {
        for(int j = 0; j < 3; j++)
        {
            if(i == 1 && j == 1) // cut out middle piece
                continue;
            QGraphicsItem *loc = new BoardGUI((ring3M->x() - 15) + (400* i), (ring3M->y()- 20) + (400 * j), std::make_pair(0,0));
            scene.addItem(loc);
        }
    }

    for(int i = 0; i <3; i++) // ring 2
    {
        for(int j = 0; j < 3; j++)
        {
            if(i == 1 && j == 1) // cut out middle piece
                    continue;
            QGraphicsItem *loc = new BoardGUI((ring2M->x()- 15) + (300* i), (ring2M->y() - 20) + (300 * j), std::make_pair(0,0));
            scene.addItem(loc);
        }
    }

    for(int i = 0; i <3; i++) // ring 1
    {
        for(int j = 0; j < 3; j++)
        {
            if(i == 1 && j == 1) // cut out middle piece
                    continue;
            QGraphicsItem *loc = new BoardGUI((ring1M->x() - 15) + (200* i), (ring1M->y() - 20) + (200 * j), std::make_pair(0,0));
            scene.addItem(loc);
        }
    }




}

void drawPieces(QGraphicsScene &scene, std::map<std::pair<char, char>, char> &gameBoard)
{
    int yOffset = 85;
    QColor currColor = Qt::black;
    for(int i = 0; i < 9; i++)
    {
        QGraphicsItem *piece = new PieceGUI(-150, (80* i) + yOffset, currColor,std::make_pair(0,0), 1);
        scene.addItem(piece);
        char ipiece = gameBoard[std::make_pair(0,0)];
    }
    currColor = Qt::white;
    for(int i = 0; i < 9; i++)
    {
        QGraphicsItem *piece = new PieceGUI(950, (80* i) + yOffset, currColor,std::make_pair(0,0), 1);
        scene.addItem(piece);
    }
}


void redrawBoard(std::pair<char, char> from, std::pair<char, char> to, QGraphicsScene * scene)
{
    scene->clear();
    drawBoard(*scene);
    //drawPieces(*scene, CV::gameBoard);
}















