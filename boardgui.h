#ifndef BOARDGUI_H
#define BOARDGUI_H
#include <Qt>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QDrag>
#include <map>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QPainter>
#include <QtWidgets>
 //this really should have been called BoardLocation


class BoardGUI : public QGraphicsItem
{
public:
    BoardGUI(int x, int y, std::pair<char, char> spot)
    {
        this->x = x;
        this->y = y;
        this->loc = spot;
        setAcceptDrops(true);
    }
    void setPos(int x, int y)
    {
            this->x = x;
            this->y = y;
    }
private:

    QRectF boundingRect() const
    {
        return QRectF(x, y, 75, 75);
    }



    std::pair<int, int> getCoord()
    {
           return std::make_pair(x,y);
    }
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) // item enters drag Rect
    {
        if (event->mimeData()->hasText())
        {
            event->setAccepted(true);
            dragOver = true;
            update();
        } else
        {
            event->setAccepted(false);
        }
    }
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) // item leaves drag Rect
    {
        Q_UNUSED(event);
        dragOver = false;
        update();
    }

    void dropEvent(QGraphicsSceneDragDropEvent *event) // dropped in bounding Rect. TODO: implement redraw
    {
        dragOver = false;
        event->setAccepted(true);
        if (event->mimeData()->hasText())
        {
            std::string s = event->mimeData()->text().toStdString();
            //redrawBoard(std::make_pair(char(s.at(0)), char(s.at(1))), square, scene());
        }
        else
        {
            update();
        }
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        painter->setBrush(dragOver ? Qt::lightGray: sColor);
        painter->drawRect(boundingRect());


    }

private:
     int x =0,  y = 0, playerPiece = 0;
     std::pair<char, char> loc;
     QColor sColor = Qt::blue;
     bool dragOver = false;

};

#endif // BOARDGUI_H
