#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>
//#include <QList>
#include <QMap>
#include "room.h"
#include "mobilenode.h"
#include "referencenode.h"
#include <QGraphicsTextItem>

class MapScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MapScene(QObject *parent = 0);
    void doMobileMsg(const QVector<int> msg);
    void doTemperatureMsg(const QVector<int> msg);
    void setFloor(int f, bool exist);
    void initReferenceNodeMap();
    int getFloor();
    void addMobileNode(int fixId, QPointF position);
    void addTemperatureNode(int floor, int number, int t);
    void moveMobileNode(MobileNode *mn, QPointF dst);
    QMap<int,MobileNode*> getMobileNodeMap();
    QMap<int,ReferenceNode *> getReferenceNodeMap();
    QMap<int,QGraphicsTextItem*> getTemperatureNodeMap();
    void showRefNode();
    void addRefNode();
    void deleteRefNode();
//    QList<Room *> roomList;
//    QMap<int, Room*> roomMap;

signals:
    void refreshEmployeeTableWidget(const int);

private:
    int floor;
    QMap<int,MobileNode*> mobileNodeMap;
    QMap<int,ReferenceNode*> referenceNodeMap;
    QMap<int,QGraphicsTextItem*> temperatureNodeMap;
};

#endif // MAPSCENE_H
