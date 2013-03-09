#include "room.h"
#include <QtGui>

Room::Room(QVector<int> msg)
{
    roomNumberColor = Qt::darkGreen;
    roomBackgroundColor = Qt::red;
    roomOutlineColor = Qt::yellow;
    QPolygonF polygon;
    for(int i=1;i<msg.size();i+=2)
    {//todo:检验输入数据长度的合法性，个人必须为单数（包含第一位）
        polygon << QPointF(msg.at(i),msg.at(i+1));
    }
    this->setPolygon( polygon);
    roomNumberPosition = QPointF(msg.at(1)+20,msg.at(2)+20);
}

Room::~Room()
{
}

QPolygonF Room::getPolygon() const
{
    return this->polygon();
}
void Room::addPosition(QPointF p)
{
    this->setPolygon(this->polygon() << p);
}

void Room::setRoomNumber(const int number)
{
    prepareGeometryChange();
    roomNumber = number;
    update();
}

int Room::getRoomNumber() const
{
    return roomNumber;
}

void Room::setTemperature(const int temperature)
{
    prepareGeometryChange();
    roomTemperature = QString::number(temperature);
    update();
}

int Room::getTemperature()
{
    bool ok;
    return roomTemperature.toInt(&ok,10);
}

void Room::setRoomNumberColor(const QColor &color)
{
    roomNumberColor = color;
    update();
}

QColor Room::getRoomNumberColor() const
{
    return roomNumberColor;
}

void Room::setRoomOutlineColor(const QColor &color)
{
    roomOutlineColor = color;
    update();
}

QColor Room::getRoomOutlineColor() const
{
    return roomOutlineColor;
}

void Room::setRoomBackgroundColor(const QColor &color)
{
    roomBackgroundColor = color;
    update();
}

QColor Room::getRoomBackgroundColor() const
{
    return roomBackgroundColor;
}

void Room::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget * widget)
{
    QPen pen(roomOutlineColor);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(roomBackgroundColor);

    painter->setPen(roomNumberColor);

    painter->setFont(QFont("Times", 20, QFont::Bold));
    painter->drawText(roomNumberPosition, roomNumber);
    painter->drawText(roomNumberPosition+QPoint(0,20),QString("%1`C").arg(roomTemperature));
    QGraphicsPolygonItem::paint(painter, option, widget);
}
