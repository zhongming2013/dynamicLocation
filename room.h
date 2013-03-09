#ifndef ROOM_H
#define ROOM_H

#include <QGraphicsItem>
#include <QPolygonF>
#include <QList>
#include <QPointF>
class QColor;

class Room : public QGraphicsPolygonItem
{
public:
    Room(QVector<int> msg);
    ~Room();
    void setRoomNumber(const QString &number);
    QString getRoomNumber() const;
    void setTemperature(const int temperature);
    int getTemperature();
    void setRoomNumberColor(const QColor &color);
    QColor getRoomNumberColor() const;
    void setRoomOutlineColor(const QColor &color);
    QColor getRoomOutlineColor() const;
    void setRoomBackgroundColor(const QColor &color);
    QColor getRoomBackgroundColor() const;

    QPolygonF getPolygon() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void addPosition(QPointF p);

private:
    QString roomNumber;
    QString roomTemperature;
    QColor roomNumberColor;
    QColor roomTemperatureColor;
    QColor roomBackgroundColor;
    QColor roomOutlineColor;
    QPointF roomNumberPosition;
};

#endif // ROOM_H
