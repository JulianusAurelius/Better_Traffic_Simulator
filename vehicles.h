#ifndef VEHICLES_H
#define VEHICLES_H

#include <QGraphicsItem>
#include <QtGui>

class Vehicles : public QGraphicsItem {
public:
    Vehicles();
    ~Vehicles() {
        delete this;
    }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    qreal speed;
    int direction;
    int slot;

protected:
    void advance(int phase) override;

private:
    QColor color;
    qreal angle;
    void DoCollision();
};

#endif // VEHICLES_H
