#include "mapscene.h"
#include "define.h"
#include "mobilenode.h"
#include "referencenode.h"

#include <QGraphicsScene>
#include <QSqlQuery>
#include <QList>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QMessageBox>
#include <QString>
#include "room.h"

MapScene::MapScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setSceneRect(0, 0, 1200, 895);//场景大小
    setBackgroundBrush(Qt::white);
}

void MapScene::addRefNode()
{
    ReferenceNode *node = new ReferenceNode;
    node->setText("ref");
    node->setPos(600,450);
    this->addItem(node);
}

void MapScene::setFloor(int f,bool exist)
{
    this->floor = f;
    if(exist)
    {
        QList<QGraphicsItem*> tempList = this->items();
        while(!tempList.isEmpty())
        {
            this->addItem(tempList.last());
            tempList.pop_back();
        }
    }
    else
    {
        addPixmap(QPixmap(tr(":/images/map%1.jpg").arg(f)));
    }
}

int MapScene::getFloor()
{
    return floor;
}

void MapScene::deleteRefNode()
{
    QList<QGraphicsItem *> items = this->selectedItems();
    QList<QGraphicsItem *>::iterator i = items.begin();
    while(i != items.end())
    {
        Node *node = dynamic_cast<Node *>(*i);
        int roomId = node->text().toInt();
        int floor,number;
        floor = roomId/100;
        number = roomId%100;
        QSqlQuery query;
        query.prepare("DELETE FROM referNode WHERE floor=? AND number=?");
        query.addBindValue(floor);
        query.addBindValue(number);
        query.exec();
        this->referenceNodeMap.remove(roomId);
        i++;
    }
    qDeleteAll(items);
}

void MapScene::showRefNode()
{
    static bool show = false;
    if(show)
    {
        QList<ReferenceNode*> nodeList = this->referenceNodeMap.values();
        while(!nodeList.isEmpty())
        {
            this->removeItem(nodeList.last());
            nodeList.pop_back();
        }
        this->referenceNodeMap.clear();
        show = false;
    }
    else
    {
        this->initReferenceNodeMap();
        QList<ReferenceNode*> nodeList = this->referenceNodeMap.values();
        while(!nodeList.isEmpty())
        {
            this->addItem(nodeList.last());
            nodeList.pop_back();
        }
        show = true;
    }
}
void MapScene::initReferenceNodeMap()
{
    QSqlQuery q;
    q.exec(QString("SELECT floor,number FROM referNode WHERE floor=%1").arg(this->floor));
    while(q.next())
    {
        int floor,number,roomId,x,y;
        floor = q.value(0).toInt();
        number = q.value(1).toInt();
        roomId = floor*100 + number;
        QSqlQuery q2;
        q2.exec(QString("SELECT x,y FROM ROOM WHERE floor=%1 AND number=%2").arg(floor).arg(number));
        q2.next();
        x = q2.value(0).toInt();
        y = q2.value(1).toInt();
        ReferenceNode *node = new ReferenceNode;
        node->setText(QString::number(roomId));
        node->setPos(x, y);
        this->referenceNodeMap.insert(floor*100+number, node);
    }
}

void MapScene::doMobileMsg(const QVector<int> msg)
{
    int roomFloor,roomNumber,fixId,help;
    QString netId;
    //两字节，低位在前，高位在后
    roomFloor = msg.at(M_ROOM_FLOOR);
    roomNumber = msg.at(M_ROOM_NUMBER);
    fixId = msg.at(M_FIXID);
    help = msg.at(M_HELP);
    netId = QString::number((msg.at(M_NETID_HI)<<8)+msg.at(M_NETID_LO),16);
    //数据合法才显示
    if(roomFloor && roomNumber)
    {
        //查询数据库获取坐标
        QSqlQuery query;
        query.exec(QString("SELECT x,y FROM room WHERE floor=%1 AND number=%2").arg(roomFloor).arg(roomNumber));
        query.next();
        int x,y;
        x = query.value(0).toInt() + (std::rand() % 20 - 10);//半径为10像素的范围
        y = query.value(1).toInt() + (std::rand() % 20 - 10);

        //向数据库添加定位记录
        query.prepare("INSERT INTO location"
                      "(fixId,netId,floor,number,help)"
                      "VALUES(?,?,?,?,?)");
        query.addBindValue(fixId);
        query.addBindValue(netId);
        query.addBindValue(roomFloor);
        query.addBindValue(roomNumber);
        query.addBindValue(help);
        query.exec();
        //节点已经存在
        if(this->mobileNodeMap.contains(fixId))
        {
            MobileNode *mn = dynamic_cast<MobileNode *>(*(this->mobileNodeMap.find(fixId)));
            mn->setHelp(help);
            if(help)
            {
                query.prepare("SELECT name FROM employee WHERE fixId = ?");
                query.addBindValue(fixId);
                query.exec();
                query.next();
                QMessageBox msgBox;
                msgBox.setText(query.value(0).toString()+" needs HELP!!!\n"
                               "He/Her is in " + QString::number(roomFloor*100+roomNumber));
                msgBox.exec();
            }
            moveMobileNode(mn,QPointF(x,y));
        }
        else
        {
            addMobileNode(fixId,QPointF(x,y));
        }
    }
}

void MapScene::doTemperatureMsg(const QVector<int> msg)
{
    int floor,number,t,roomId;
    floor = msg.at(RT_ROOM_FLOOR);
    number = msg.at(RT_ROOM_NUMBER);
    t = msg.at(RT_ROOM_TEMP);
    roomId = floor*100 + number;
    if(this->temperatureNodeMap.contains(roomId))
    {//更新显示温度
        QGraphicsTextItem * tn = this->temperatureNodeMap.value(roomId);
        tn->setPlainText(QString("%1`C").arg(t));
    }
    else
    {//添加温度节点
        addTemperatureNode(floor, number, t);
    }
    QSqlQuery q;//温度数据记录到数据
    q.prepare("INSERT INTO temperature (floor,number,temperature)"
              "VALUES (?,?,?)");
    q.addBindValue(floor);
    q.addBindValue(number);
    q.addBindValue(t);
    q.exec();
}

void MapScene::addMobileNode(int fixId, QPointF position)
{
    MobileNode *node = new MobileNode(this);
    node->setText(tr("%1").arg(fixId));
    node->setPos(position);
    //选中后更新员工信息窗口
    connect(node, SIGNAL(itemSelected(const int)),
            this, SIGNAL(refreshEmployeeTableWidget(const int)));
    this->addItem(node);
    this->mobileNodeMap.insert(fixId,node);
}

//创建温度节点，并添加到scene和添加到scene的temperatureNodeMap
void MapScene::addTemperatureNode(int floor,int number, int t)
{
    QGraphicsTextItem *temp = new QGraphicsTextItem(QString("%1`C").arg(t));
    QSqlQuery q;
    int x,y;
    q.exec(QString("SELECT x,y FROM room WHERE floor=%1 AND number=%2").arg(floor).arg(number));
    if(q.next())
    {
        x = q.value(0).toInt() - 50;
        y = q.value(1).toInt() - 50;
    }
    temp->setPos(x,y);
    this->addItem(temp);
    this->temperatureNodeMap.insert(floor*100+number,temp);
}

void MapScene::moveMobileNode(MobileNode *mn, QPointF dst)
{
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    QTimeLine *timer = new QTimeLine(1500);

    animation->setItem(mn);
    animation->setPosAt(1.0, dst);
    animation->setTimeLine(timer);
    timer->start();
}

QMap<int,MobileNode*> MapScene::getMobileNodeMap()
{
    return this->mobileNodeMap;
}

QMap<int,ReferenceNode*> MapScene::getReferenceNodeMap()
{
    return this->referenceNodeMap;
}

QMap<int,QGraphicsTextItem *> MapScene::getTemperatureNodeMap()
{
    return this->temperatureNodeMap;
}
