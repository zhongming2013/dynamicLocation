#ifndef ROOMBLOCK_H
#define ROOMBLOCK_H

#include <QColor>
#include <QGraphicsItem>
#include <QPainterPath>

class QGradient;

class RoomBlock : public QGraphicsItem
{
public:
    enum Kind { Park, SmallBuilding, Hospital, Hall, Building, Tower,
                LShapedBlock, LShapedBlockPlusSmallBlock, TwoBlocks,
                BlockPlusTwoSmallBlocks };

    RoomBlock(Kind kind);

    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int kind;
    QColor color;
    QPainterPath shape;
};

#endif // ROOMBLOCK_H
