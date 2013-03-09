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
    if(change == QGraphicsItem::ItemSelectedChange)//Node��ѡ�У����ʱ����һ�Σ��ӵ������������ִ���һ��
    {
        emit itemSelected(this->text().toInt());//�����ź�
    }

    return QGraphicsItem::itemChange(change, value);
}

void MobileNode::timerEvent(QTimerEvent *e)//��˸Ч��
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
