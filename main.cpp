#include <QtMath>
#include <QtWidgets>
#include "trafficlights.h"
#include "vehicles.h"
#include <QRandomGenerator>

static constexpr int VehicleCount = 3;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QGraphicsScene scene;
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    QGraphicsView view(&scene);
    view.QWidget::setFixedSize(900, 700);
    scene.setSceneRect(0, 0, 800, 600);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QPixmap("C:/Users/brand/Pictures/Intersection.png")); //fix this

    for(int i = 0; i < VehicleCount; ++i) {
        Vehicles *vehicle = new Vehicles;
        scene.addItem(vehicle);
    }
    //slot and direction will be randomized for now, speed later.

    //Trafficlights *tf1 = new Trafficlights;
    //Trafficlights *tf2 = new Trafficlights;
    //Trafficlights *tf3 = new Trafficlights;
    //Trafficlights *tf4 = new Trafficlights;

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    QPen border = QPen(Qt::transparent);
    QLineF TopLine(scene.sceneRect().topLeft(), scene.sceneRect().topRight());
    QLineF LeftLine(scene.sceneRect().topLeft(), scene.sceneRect().bottomLeft());
    QLineF RightLine(scene.sceneRect().topRight(), scene.sceneRect().bottomRight());
    QLineF BottomLine(scene.sceneRect().bottomLeft(), scene.sceneRect().bottomRight());

    scene.addLine(TopLine, border);
    scene.addLine(LeftLine, border);
    scene.addLine(RightLine, border);
    scene.addLine(BottomLine, border);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Traffic Simulator"));
    view.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 66);

    return app.exec();
}
