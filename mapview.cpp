#include <QtGui>
#include <cmath>

#include "mapview.h"
#include "mapscene.h"

MapView::MapView(QWidget *parent)
    : QGraphicsView(parent)
{
    setDragMode(ScrollHandDrag);
    setRenderHints(QPainter::Antialiasing
                   | QPainter::TextAntialiasing);//�����
}

void MapView::wheelEvent(QWheelEvent *event)
{
    double numDegrees = -event->delta() / 8.0;
    double numSteps = numDegrees / 15.0;
    double factor = std::pow(1.125, numSteps);
    scale(factor, factor);
}

void MapView::switchScenes()
{
    //ʹ���б��洴�������г��������ݿ�ҲҪ��ƺ���
    int newFloor = QInputDialog::getInt(this, tr("Enter New Floor Number"), tr("Floor:"),6);

    if(this->sceneMap.contains(newFloor))
    {
        MapScene * scene = this->sceneMap.value(newFloor);
        this->setScene(scene);
        this->setCurrentScene(scene);
    }
    else
    {
        MapScene *scene = new MapScene;
        scene->setFloor(newFloor,false);
        this->addScene(newFloor,scene);
        this->setScene(scene);
        this->setCurrentScene(scene);
    }
}

void MapView::addScene(int floor, MapScene *scene)
{
    this->sceneMap.insert(floor, scene);
}

void MapView::setCurrentScene(MapScene *scene)
{
    this->currentScene = scene;
}

MapScene* MapView::getCurrentScene()
{
    return this->currentScene;
}

void MapView::sceneAddReferNode()
{
    this->currentScene->addRefNode();
}

void MapView::sceneDeleteReferNode()
{
    this->currentScene->deleteRefNode();
}

void MapView::sceneShowReferNode()
{
    this->currentScene->showRefNode();
}

MapScene* MapView::getScene(int floor)
{//TODO:�������봦��
    if(this->sceneMap.contains(floor))
        return this->sceneMap.value(floor);
}
