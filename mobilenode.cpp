#include "mobilenode.h"

#include <QTimerEvent>
#include <QDebug>

MobileNode::MobileNode(QObject *parent) : QObject(parent)
{
    help = 0;
    timerId1 = startTimer(1500);

    setFlags(ItemIsSelectable);
}
MobileNode::~MobileNode()
{

}

void MobileNode::setHelp(int h)
{
    help = h;
}

int MobileNode::getHelp()
{
    return help;
}

QVariant MobileNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemSelectedChange)//Node被选中，点击时触发一次，从点击到不被点击又触发一次
    {
        emit itemSelected(this->text().toInt());//发送信号
    }

    return QGraphicsItem::itemChange(change, value);
}

void MobileNode::timerEvent(QTimerEvent *e)//闪烁效果
{
    if(timerId1 == e->timerId())
    {
        if(help)
            this->setBackgroundColor(Qt::red);
        else
            this->setBackgroundColor(Qt::blue);
        timerId2 = startTimer(200);
    }
    if(timerId2 == e->timerId())
    {
        if(help)
            this->setBackgroundColor(Qt::darkRed);
        else
            this->setBackgroundColor(Qt::darkBlue);
        killTimer(timerId2);
    }
}
