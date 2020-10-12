#ifndef PIECEGUI_H
#define PIECEGUI_H

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


class PieceGUI :public QGraphicsItem
{
public:
    PieceGUI();
    PieceGUI(int x, int y, QColor sColor, std::pair<char,char> spot, int player) //constructor
    {
        this-> x = x;
        this-> y = y;
        this->currColor = sColor;
        this->spot = spot;
        this->playerPiece = player;
    }
    void setPos(int x, int y) //IEEE point
    {
        this->x = x;
        this->y = y;
    }
    void setPos(QPointF p) //graphical point
    {
        this->x = p.x();
        this->y = p.y();
    }

    QRectF boundingRect() const //bound of selection
    {
        return QRectF(x, y, 40, 40);
    }

    QRectF interior() const //interior selection
    {
        return QRectF(x+2, y+2, 33, 33);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent * event){
        setCursor(Qt::ClosedHandCursor);
        event->setAccepted(true);
        update();
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent * event) //Mouse drag
       {
           if (QLineF(event->screenPos(),
                     event->buttonDownScreenPos(Qt::LeftButton)).length() < QApplication::startDragDistance()) {
              return;
           }

           QRect rect = boundingRect().toRect();

           //An attempt at making drag animation
           QPixmap pixmap(rect.size());
           pixmap.fill(Qt::transparent);
           pixmap.scaled(10,10);
           QPainter painter(&pixmap);

           painter.translate(-rect.topLeft());

           painter.setBrush(Qt::lightGray);

           painter.drawEllipse(QPoint(x+40/3, y+40/3), 75/3, 75/3);

           painter.setBrush(currColor);
           painter.drawEllipse(QPoint(x+40/3, y+40/3), 33/3, 33/3);
           painter.setBrush(Qt::black);
           painter.end();

           QDrag *drag = new QDrag(event->widget());
           drag->setHotSpot( QPoint( 40/3, 40/3 ) );
           drag->setPixmap(pixmap);

           QMimeData *mime = new QMimeData;
           QString s;
           s += spot.first;
           s += spot.second;

           mime->setText(s);
           drag->setMimeData(mime);

           //hide();
           update();
           drag->exec();
       }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) //when mouse is released
        {
            show();
            setCursor(Qt::OpenHandCursor);
            event->setAccepted(true);
        }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option = 0, QWidget *widget = 0)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        painter->setBrush(Qt::lightGray);

        painter->drawEllipse(boundingRect());

        painter->setBrush(currColor);
        painter->drawEllipse(interior());
        painter->setBrush(Qt::black);
    }

private:
    int x = 0, y = 0;
    std::pair<char, char> spot = std::make_pair('a', '1'); // location
    QColor currColor = Qt::black; //default is black
    int playerPiece = 1; //determines who owns the piece



};

























#endif // PIECEGUI_H
