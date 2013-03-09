#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QList>

#include "mapscene.h"

class MapView : public QGraphicsView
{
    Q_OBJECT

public:
    MapView(QWidget *parent = 0);
    void addScene(int floor, MapScene* scene);
    void setCurrentScene(MapScene * scene);
    MapScene* getCurrentScene();
    MapScene* getScene(int floor);

private slots:
    void switchScenes();
    void sceneAddReferNode();
    void sceneShowReferNode();
    void sceneDeleteReferNode();


protected:
    void wheelEvent(QWheelEvent *event);

private:
    QMap<int,MapScene *> sceneMap;
    MapScene *currentScene;
};

#endif // MAPVIEW_H
