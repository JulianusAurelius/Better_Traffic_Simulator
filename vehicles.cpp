#include "vehicles.h"
#include <QGraphicsScene>
#include <QtMath>
#include <QStyleOption>
#include <QPainter>
#include <QRandomGenerator>
#include <QDebug>
//for the colors, just use a basic default.

constexpr qreal Pi = M_PI;
constexpr qreal slotX1 = 25.0;
constexpr qreal slotY1 = 330.0;
constexpr qreal slotX2 = 360.0;
constexpr qreal slotY2 = 25.0;
constexpr qreal slotX3 = 775.0;
constexpr qreal slotY3 = 270.0;
constexpr qreal slotX4 = 450.0;
constexpr qreal slotY4 = 575.0;
constexpr int NORTH = 180;
constexpr int SOUTH = 0;
constexpr int EAST = 270;
constexpr int WEST = 90;

static int startX, startY;
qreal turnL, turnR, prAngle, plAngle;
QPointF Pr, Pl; //RIGHT = 270, LEFT = 90, DOWN = 0, UP = 180

static int generateSlot (int &slot) {
    if (slot == 0) { //right
        startX = slotX1;
        startY = slotY1;
        turnR = slotX1 + 325;
        turnL = slotX1 + 425;
        Pr = QPointF(turnR, slotY1);
        Pl = QPointF(turnL, slotY1);
        prAngle = 0;
        plAngle = 180;
        return 270;
    } else if (slot == 1) { //down
        startX = slotX2;
        startY = slotY2;
        turnR = slotY2 + 200;
        turnL = slotY2 + 350;
        Pr = QPointF(slotX2, turnR);
        Pl = QPointF(slotX2, turnL);
        prAngle = 90;
        plAngle = 270;
        return 0;
    } else if (slot == 2) { //left
        startX = slotX3;
        startY = slotY3;
        turnR = slotX3 - 325;
        turnL = slotX3 - 425;
        Pr = QPointF(turnR, slotY3);
        Pl = QPointF(turnL, slotY3);
        prAngle = 180;
        plAngle = 0;
        return 90;
    } else if (slot == 3) { //up
        startX = slotX4;
        startY = slotY4;
        turnR = slotY4 - 250;
        turnL = slotY4 - 550;
        Pr = QPointF(slotX4, turnR);
        Pl = QPointF(slotX4, turnL);
        prAngle = 270;
        plAngle = 90;
        return 180;
    }

    return 0;
}

Vehicles::Vehicles() : color (QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256),
    QRandomGenerator::global()->bounded(256))
{
    slot = QRandomGenerator::global()->bounded(4);
    angle = generateSlot(slot);
    direction = QRandomGenerator::global()->bounded(2);
    speed = 1; //will change
    setPos(startX, startY);
}

QRectF Vehicles::boundingRect() const {
    return QRectF(-20, -20, 20, 20);
}

QPainterPath Vehicles::shape() const {
    QPainterPath dim;
    dim.addRect(-20,-20,20,20);
    return dim;
}

void Vehicles::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(color);
    painter->drawEllipse(-20, -20, 20, 20);

    if(scene()->collidingItems(this).isEmpty()){
        //no collision
    } else {
        hide(); //delete object in the future TODO"
        DoCollision();
    }
}



void Vehicles::advance(int phase) {
    if(!phase) return;

    QPointF location = this->pos();
    setRotation(angle); //RIGHT = 270, LEFT = 90, DOWN = 0, UP = 180
    setPos(mapToParent(0, (speed)));

    if(direction == 0) { //right
        if(location == Pr) {
            angle = prAngle;
        }
    } else if (direction == 1) { //left
        if(location == Pl) {
            angle = plAngle;
        }
        //right
    //Turn right or left, else go forward
 //   if(location == QPointF(450.0, 330.0)) {
 //       angle = 180;
 //   } //turn right
  //    if(location == QPointF(startX + 325.0, startY)) { //turn right
  //        angle = 0;
  //    }
    }
}

void Vehicles::DoCollision()
{
        //TODO:
}

