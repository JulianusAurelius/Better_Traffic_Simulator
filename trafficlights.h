#ifndef TRAFFICLIGHTS_H
#define TRAFFICLIGHTS_H

#include <QGraphicsItem>

class Trafficlights : public QGraphicsItem
{
    Q_OBJECT

public:
    explicit Trafficlights(QWidget *parent = nullptr);
    ~Trafficlights();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    void Status_Green();
    void Status_Yellow();
    void Status_Red();
private:
    int lightStatus; //time
    void estTime();
};

#endif // TRAFFICLIGHTS_H
