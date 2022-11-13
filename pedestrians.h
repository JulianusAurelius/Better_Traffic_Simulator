#ifndef PEDESTRIANS_H
#define PEDESTRIANS_H

#include <QDialog>
#include <QGraphicsItem>

namespace Ui {
class Pedestrians;
}

class Pedestrians : public QGraphicsItem
{
    Q_OBJECT

public:
    explicit Pedestrians(QWidget *parent = nullptr);
    ~Pedestrians();

private:
    Ui::Pedestrians *ui;
};

#endif // PEDESTRIANS_H
